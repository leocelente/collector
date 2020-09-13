#ifndef INVERT_INDEX_H
#define INVERT_INDEX_H

#include <leveldb/db.h>
#include <optional>
#include <string>
#include <vector>

using UrlId = uint64_t;

class InvIndexStorage {
public:
  InvIndexStorage();
  ~InvIndexStorage();
  bool add(const std::string &token, const UrlId index) const;
  [[nodiscard]] std::vector<UrlId> find(const std::string &token) const;

private:
  leveldb::DB *db;
};

#endif // !INVERT_INDEX_H
