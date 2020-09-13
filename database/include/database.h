#ifndef _DATABASE_H_
#define _DATABASE_H_

#include <memory>
#include <optional>
#include <string>
#include <vector>
#include "./url_db.h"
#include "./inverted_index.h"

namespace db {
using UrlId = uint64_t;

class Database {
public:
  bool add(const std::string& url, const std::vector<std::string>& tokens)const;
  [[nodiscard]]std::vector<std::string> find(const std::string& token) const;

private:
  InvIndexStorage indexes;
  UrlStorage urls;
};

} // namespace db
#endif // !_DATABASE_H_
