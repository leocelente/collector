#include "../include/nlp.h"
#include <mitie/named_entity_extractor.h>
#include <mitie/conll_tokenizer.h>
#include <iostream>
#include <string>
using namespace nlp;
EntityExtractor::EntityExtractor(const std::string model_filename){
    std::cout << "Starting Entity Extractor with model: " << model_filename << std::endl;
}

/**
 * @brief 
 * ! do this
 * ? is this the best
 * TODO: a thing 
 * @param file_content 
 * @return std::vector<std::string> 
 */
TokenCount EntityExtractor::reToken(){
    std::cout << "Extracting Tokens from "  << std::endl;
    return TokenCount{};
}
