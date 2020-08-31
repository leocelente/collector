#include "../include/collector.h"

int main(int argc, const char** argv) {
    auto extractor = nlp::EntityExtractor("my_model.dat");
    const std::string file_contents = "a very long string that contains Zenith and I2C";
    const auto aToken = extractor.reToken();
    
    return 0;
}
