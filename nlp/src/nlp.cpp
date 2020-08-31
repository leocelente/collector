#include "../include/nlp.h"
#include <iostream>
#include <mitie/conll_tokenizer.h>
#include <mitie/named_entity_extractor.h>
#include <string>
using namespace nlp;
EntityExtractor::EntityExtractor(const std::string model_filename) {
  std::cout << "Starting Entity Extractor with model: " << model_filename
            << std::endl;
}

/**
 * @brief
 * ! do this
 * ? is this the best
 * TODO: a thing
 * @param file_content
 * @return std::vector<std::string>
 */
std::vector<std::string> EntityExtractor::extract(std::string_view contents) {
    std::vector<std::string> out {"Zenith", "I2C"};
    return std::move(out);
}
