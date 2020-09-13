#ifndef URL_DB_H
#define URL_DB_H

#include <leveldb/db.h>
#include <optional>
#include <string>
#include <vector>

using UrlId = uint64_t;

class UrlStorage {
public:
  UrlStorage();
  ~UrlStorage();
  std::optional<UrlId> add(const std::string url);
  std::optional<std::string> find(UrlId index);

private:
  leveldb::DB *db;
};

#endif // !URL_DB_H
