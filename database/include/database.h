#ifndef _DATABASE_H_
#define _DATABASE_H_

#include <leveldb/db.h>
#include <memory>
#include <optional>
#include <string>
#include <vector>
  
namespace db {
using UrlId = uint64_t;

class InvIndexStorage {
public:
  InvIndexStorage();
  InvIndexStorage(InvIndexStorage &&) = default;
  InvIndexStorage(const InvIndexStorage &) = default;
  InvIndexStorage &operator=(InvIndexStorage &&) = default;
  InvIndexStorage &operator=(const InvIndexStorage &) = default;
  ~InvIndexStorage();
  bool add(std::string token, UrlId index);

private:
  leveldb::DB* db;
};

class UrlStorage {
public:
  UrlStorage();
  UrlStorage(UrlStorage &&) = default;
  UrlStorage(const UrlStorage &) = default;
  UrlStorage &operator=(UrlStorage &&) = default;
  UrlStorage &operator=(const UrlStorage &) = default;
  ~UrlStorage();
  std::optional<UrlId> add(const std::string url);
private:
  leveldb::DB* db;

};

class Database {
public:
  Database();
  Database(Database &&) = default;
  Database(const Database &) = default;
  Database &operator=(Database &&) = default;
  Database &operator=(const Database &) = default;
  ~Database() = default;

  bool add(std::string url, std::vector<std::string> tokens);

private:
  InvIndexStorage indexes;
  UrlStorage urls;
};

} // namespace db

#endif // !_DATABASE_H_
