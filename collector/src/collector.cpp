#include "../include/collector.h"
#include <fstream>
#include <iostream>

int main(int argc, const char **argv) {
  std::cout << "Loading NER Model...\n";
  auto extractor = nlp::EntityExtractor("./models/ner_model.dat");

  std::string filename{"./sample_txt/IIC.txt"};
  const auto entities = extractor.extract(filename);

  auto database = db::Database();
  auto ok = database.add(filename, entities);
  if (!ok) {
    std::cerr << "Failed to Save to Database\n";
  }
  std::cout << "Searching for: " << entities[0] << '\n';
  auto results = database.find(entities[0]);
  for(const auto& url : results){
    std::cout << url << '\n';
  }
  return 0;
}
