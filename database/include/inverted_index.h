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
  bool add(std::string token, UrlId index);
  std::vector<UrlId> find(std::string token);

private:
  leveldb::DB *db;
};

#endif // !INVERT_INDEX_H
