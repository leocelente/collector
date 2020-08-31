#ifndef _DATABASE_H_
#define _DATABASE_H_

#include <string>
#include <optional>
#include <vector>

namespace db {
using UrlId = int; 


class InvIndexStorage {
public:
  InvIndexStorage();
  InvIndexStorage(InvIndexStorage &&) = default;
  InvIndexStorage(const InvIndexStorage &) = default;
  InvIndexStorage &operator=(InvIndexStorage &&) = default;
  InvIndexStorage &operator=(const InvIndexStorage &) = default;
  ~InvIndexStorage() = default;
    bool add(std::string token, UrlId index);
private:
};

class UrlStorage {
public:
  UrlStorage();
  UrlStorage(UrlStorage &&) = default;
  UrlStorage(const UrlStorage &) = default;
  UrlStorage &operator=(UrlStorage &&) = default;
  UrlStorage &operator=(const UrlStorage &) = default;
  ~UrlStorage() = default;
    std::optional<UrlId> add(const std::string url);    
 private:
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
