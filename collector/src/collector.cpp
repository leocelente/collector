#include "../include/collector.h"
#include <fstream>
#include <iostream>

int main(int argc, const char **argv) {
  auto extractor = nlp::EntityExtractor("my_model.dat");

  // std::ifstream file_stream("./sample_txt/i2c.txt");
  std::string filename{"./sample_txt/i2c.txt"};
  const auto tokens = extractor.extract(filename);
  for (const auto &tok : tokens) {
    std::cout << '\n' << tok << '\n';
  }
  auto database = db::Database();
  auto ok = database.add("http://myurl.com/tutorial", tokens);
  if (!ok) {
    std::cerr << "Failed to Save to Database\n";
  }
  return 0;
}
