#include "../include/database.h"
#include <cassert>
#include <iostream>
#include <leveldb/db.h>
#include <optional>

using namespace db;
Database::Database() { std::cout << "Starting Database Service\n"; }

bool Database::add(std::string url, std::vector<std::string> tokens) {
  std::cout << "Processing URL: " << url << '\n';
  auto index = this->urls.add(url);
  if (!index) {
    std::cerr << "Could not save URL\n";
  }
  std::cout << "Saving URL\n";
  for (const auto token : tokens) {
    auto ok = this->indexes.add(token, index.value());
    if (!ok) {
      return false;
    }
  }
  return true;
}

InvIndexStorage::InvIndexStorage() {
  std::cout << "Starting InvIndex Storage\n";
}

bool InvIndexStorage::add(std::string token, UrlId id) {
  std::cout << "Addding token: '" << token << "' to id: " << id << '\n';
  return true;
}

UrlStorage::UrlStorage() {
  std::cout << "Starting Url Storage\n";
  leveldb::Options options;
  options.create_if_missing = true;
  leveldb::Status status =
      leveldb::DB::Open(options, "/tmp/urlsdb", &(this->db));
  assert(status.ok());
}

UrlStorage::~UrlStorage() { delete db; }

void const num_to_bytes(uint64_t n, uint32_t len, uint8_t *dest) {
  while (len--) {
    dest[len] = (uint8_t)n;
    n >>= 8;
  }
}

std::optional<UrlId> UrlStorage::add(const std::string url) {
  std::string value;
  std::hash<std::string> hasher;
  uint64_t hashed_url = hasher(url);
  std::cout << "HASH: '" << hashed_url << "'\n";

  uint8_t blob[8] = {0xDE, 0xAD, 0xBE, 0xEF, 0xDE, 0xAD, 0xBE, 0xEF};
  num_to_bytes(hashed_url, sizeof(hashed_url), blob);

  leveldb::Slice key2((char *)blob, 8);

  auto s = db->Get(leveldb::ReadOptions(), key2, &value);
  if (s.ok()) {
    // Do nothing
    std::cout << "Entry was already in Database\n";
  } else if (s.IsNotFound()) {
    std::cout << "Writing value\n";
    s = db->Put(leveldb::WriteOptions(), key2, url);
  } else {
    return {}; // false std::optional
  }
  // ? Checks 
  // s = db->Get(leveldb::ReadOptions(), key2, &value); 
  // std::cout << "Value should now be: '" << value << "'\n";
  return hashed_url;
}
