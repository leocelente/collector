#include "../include/collector.h"
#include <fstream>
#include <iostream>
#include <regex>

int main(int argc, const char **argv) {
  std::cout << "Loading NER Model..." << std::fflush;
  auto extractor = nlp::EntityExtractor("./models/ner_model.dat");
  std::cout << "OK" << std::endl;

  std::string cmd;
  std::string arg;
  const std::regex is_exit("^(exit|EXIT)$");
  const std::regex is_add("^(add|ADD)");
  const std::regex is_url("([[:graph:]]+)");
  const std::regex is_find("^(search|SEARCH)");
  const std::regex is_term("([[:alnum:]]+)");
  std::smatch cmd_match;
  std::smatch arg_match;

  do {
    std::cout << ">";
    std::cin >> cmd;
    std::cin >> arg;
    if (std::regex_match(cmd, cmd_match, is_add) &&
        std::regex_match(arg, arg_match, is_url)) {

      std::ssub_match action_match = cmd_match[0];
      std::string action = action_match.str();
      std::cout << "  [adding]: '" << action << "'";
      std::ssub_match url_match = arg_match[0];
      std::string url = url_match.str();
      std::cout << "  url: " << url << '\n';

    } else if (std::regex_match(cmd, cmd_match, is_find) &&
               std::regex_match(arg, arg_match, is_term)) {

      std::ssub_match action_match = cmd_match[0];
      std::string action = action_match.str();
      std::cout << "  [searching]: '" << action << "'";
      std::ssub_match url_match = arg_match[0];
      std::string url = url_match.str();
      std::cout << "  term: " << url << '\n';

    } else {
      std::cout << "[*] Not a valid command!\n";
    }
  } while (!std::regex_match(cmd, cmd_match, is_exit));

  for (size_t i = 0; i < 2; i++) {
    std::string filename{"./sample_txt/IIC.txt"};
    const auto database = db::Database();

    if (database.check(filename)) {
      std::cout << "This file is already in the database\n";
      continue;
    }
    const auto entities = extractor.extract(filename);

    const auto ok = database.add(filename, entities);
    if (!ok) {
      std::cerr << "Failed to Save to Database\n";
    }
    std::cout << "Searching for: " << entities[0] << '\n';
    const auto results = database.find(entities[0]);
    for (const auto &url : results) {
      std::cout << url << '\n';
    }
  }

  return 0;
}
