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
  std::optional<UrlId> add(const std::string &url) const;
  [[nodiscard]] std::optional<std::string> find(const UrlId index) const;
  /**
   * @brief Checks if url is in the Database
   * 
   * @param url 
   * @return true -> url IS in database
   * @return false -> url is NOT in database
   */
  [[nodiscard]] bool check(const std::string &url) const;

private:
  leveldb::DB *db;
};

#endif // !URL_DB_H
