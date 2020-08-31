#include "../include/collector.h"
#include <iostream>
int main(int argc, const char** argv) {
    auto extractor = nlp::EntityExtractor("my_model.dat");
    const std::string file_contents = "a very long string that contains Zenith and I2C";
    const auto tokens = extractor.extract(file_contents);
    

    auto database = db::Database();
    auto err = database.add("http://myurl.com/tutorial", tokens);
    if(err){
        std::cerr << "Failed to Save to Database\n";
    }
    return 0;
}
