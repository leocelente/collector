#include "../include/nlp.h"
#include <iostream>
#include <mitie/conll_tokenizer.h>
#include <mitie/named_entity_extractor.h>
#include <string>

nlp::EntityExtractor::EntityExtractor(const std::string model_filename) {
  std::cout << "Starting Entity Extractor with model: " << model_filename
            << std::endl;
}

std::vector<std::string> nlp::EntityExtractor::extract(std::string &filename) {
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
  return tokens;
}

void nlp::EntityExtractor::filter() {}
void nlp::EntityExtractor::named_entities() {}

// namespace nlp
