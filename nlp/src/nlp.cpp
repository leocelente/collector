#include "../include/nlp.h"
#include <iostream>
#include <mitie/conll_tokenizer.h>
#include <mitie/named_entity_extractor.h>
#include <string>

using namespace nlp;

EntityExtractor::EntityExtractor(const std::string& model_filename_)
    : model_file(model_filename_) {}

// ? possible string_view
std::vector<std::string> EntityExtractor::extract(const std::string &filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cout << "Unable to load input text file" << std::endl;
    throw;
  }
  mitie::conll_tokenizer tokenizer(file);
  std::vector<std::string> tokens;
  std::string token;
  while (tokenizer(token)) {
    tokens.emplace_back(token);
  }
  return named_entities(tokens);
}

std::vector<std::string>
EntityExtractor::named_entities(std::vector<std::string> &tokens) {

  // ! This is a problem,  the deserialization takes a long time
  // ! It must not be done in every extraction
  mitie::named_entity_extractor ner{}; // create entity extractor
  std::string classname;
  dlib::deserialize(this->model_file) >> classname >> ner; // load ml model
  std::cout << classname << '\n';
  std::vector<pair<size_t, size_t>> chunks;
  std::vector<size_t> chunk_tags;
  std::vector<double> chunk_scores;

  ner.predict(tokens, chunks, chunk_tags, chunk_scores);

  std::vector<std::string> all_entities{};
  for (const auto chunk : chunks) {
    for (size_t j = chunk.first; j < chunk.second; ++j) {
      all_entities.emplace_back(tokens[j]);
    }
  }
  return filter(all_entities);
}

std::vector<std::string>
EntityExtractor::filter(std::vector<std::string> entities) {
  std::vector<std::string> repeated_tokens{};
  std::sort(entities.begin(), entities.end());
  notunique_sorted(entities.begin(), entities.end(),
                   std::back_inserter(repeated_tokens));

  auto it_tok = repeated_tokens.begin();
  std::vector<TokenCount> count{};
  while (it_tok != repeated_tokens.end()) {
    auto prev = it_tok++;
    it_tok = std::adjacent_find(it_tok, repeated_tokens.end(),
                                std::not_equal_to<std::string>());
    size_t cnt = std::distance(prev, it_tok);
    if (it_tok == repeated_tokens.end()) {
      count.emplace_back(*prev, cnt);
      break;
    } else {
      count.emplace_back(*it_tok, cnt);
    }
  }
  constexpr int N = 5;
  std::vector<TokenCount> top_entities(N);
  std::partial_sort_copy(count.begin(), count.end(), top_entities.begin(),
                         top_entities.end());

  std::vector<std::string> filtered_entities;
  std::transform(top_entities.begin(), top_entities.end(),
                 std::back_inserter(filtered_entities),
                 [](const auto &cp) { return cp.token; });
  return filtered_entities;
}

TokenCount::TokenCount(const std::string &token_, const int count_)
    : token(token_), count(count_) {}
