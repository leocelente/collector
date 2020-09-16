#include "../include/collector.h"
#include <fstream>
#include <iostream>

int main(int argc, const char **argv) {
  std::cout << "Loading NER Model..." << std::fflush;
  auto extractor = nlp::EntityExtractor("./models/ner_model.dat");
  std::cout << "OK" << std::endl;

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
