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
  std::vector<UrlId> find(std::string token);

private:
  leveldb::DB *db;
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
  std::optional<std::string> find(UrlId index);

private:
  leveldb::DB *db;
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
  std::vector<std::string> find(std::string token);

private:
  InvIndexStorage indexes;
  UrlStorage urls;
};

} // namespace db
inline void const num_to_bytes(uint64_t n, uint32_t len, uint8_t *dest) {
  while (len--) {
    dest[len] = (uint8_t)n;
    n >>= 8;
  }
}
inline uint64_t const bytes_to_num(uint32_t len, uint8_t *arr) {
  uint64_t n;
  uint32_t i = 0;
  while (i < len) {
    n <<= 8;
    n += arr[i++];
  }
  return n;
}
#endif // !_DATABASE_H_

/**
 * @brief
 * 12064514428219666312
 * 2496611203689696685
 * 12086069859412187181
 *
 * 12064514428219666312
 * 2496611203689696685
 * 12086069859412187181
 */
