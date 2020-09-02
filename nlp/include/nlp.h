#ifndef _NLP_H_
#define _NLP_H_
#include <string>
#include <string_view>
#include <vector>

namespace nlp {

class TokenCount {
    std::string token;
    int count = 0;
    bool operator<(const TokenCount& other) const {
        return this->count < other.count;
    } 
};

class EntityExtractor {
public:
  EntityExtractor(const std::string model_filename);
  std::vector<std::string> extract(std::string& filename);

private:
    void all_tokens(std::ifstream& file_stream);
    void filter();
    void named_entities();
    std::vector<std::string> tokens;
};

} // namespace nlp
#endif // !_NLP_H_
