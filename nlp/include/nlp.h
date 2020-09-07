#ifndef _NLP_H_
#define _NLP_H_
#include <algorithm>
#include <string>
#include <string_view>
#include <vector>

namespace nlp {

struct TokenCount {
  TokenCount(std::string token, int count);
  TokenCount() = default;
  std::string token;
  int count = 0;

  bool operator<(const TokenCount &other) const {
    return other.count < this->count;
  }
};

class EntityExtractor {
public:
  EntityExtractor(const std::string model_filename);
  std::vector<std::string> extract(std::string &filename);

private:
  void all_tokens(std::ifstream &file_stream);
  std::vector<std::string> filter(std::vector<std::string> entities);
  std::vector<std::string> named_entities(std::vector<std::string> &tokens);
  // std::vector<std::string> tokens;
  std::string model_file;
};

} // namespace nlp

template <class ForwardIt, class OutIt>
inline void notunique_sorted(const ForwardIt first, const ForwardIt last,
                             OutIt out) {
  auto it = std::adjacent_find(first, last);
  while (it != last) {
    *out++ = (*it++);
    it = std::adjacent_find(it, last);
  }
}
#endif // !_NLP_H_
