#ifndef _NLP_H_
#define _NLP_H_
#include <string>
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
  TokenCount reToken();
private:
    
};

} // namespace nlp
#endif // !_NLP_H_
