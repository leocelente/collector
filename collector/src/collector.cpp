#include "../include/collector.h"
#include <fstream>
#include <iostream>

int main(int argc, const char **argv) {
  auto extractor = nlp::EntityExtractor("./models/ner_model.dat");

  std::string filename{"./sample_txt/IIC.txt"};
  const auto entities = extractor.extract(filename);
  std::cout << "Found " << entities.size() << " entities\n";
  
  auto database = db::Database();
  auto ok = database.add(filename, entities);
  if (!ok) {
    std::cerr << "Failed to Save to Database\n";
  }

  database.find(entities[0]);
  return 0;
}
