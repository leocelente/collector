#include "../include/url_db.h"
#include <iostream>

static void const num_to_bytes(uint64_t n, uint32_t len, uint8_t *dest) {
  while (len--) {
    dest[len] = (uint8_t)n;
    n >>= 8;
  }
}
static uint64_t const bytes_to_num(uint32_t len, uint8_t *arr) {
  uint64_t n;
  uint32_t i = 0;
  while (i < len) {
    n <<= 8;
    n += arr[i++];
  }
  return n;
}

UrlStorage::UrlStorage() {
  leveldb::Options options;
  options.create_if_missing = true;
  leveldb::Status status =
      leveldb::DB::Open(options, "/tmp/urlsdb", &(this->db));
  assert(status.ok());
}

UrlStorage::~UrlStorage() { delete db; }

std::optional<UrlId> UrlStorage::add(const std::string &url) const {
  const UrlId hashed_url = std::hash<std::string>()(url);
  // Conversion to Slice
  std::array<uint8_t, sizeof(UrlId)> blob;
  num_to_bytes(hashed_url, blob.size(), blob.data());
  leveldb::Slice key((char *)blob.data(), blob.size());

  std::string value;
  auto s = db->Get(leveldb::ReadOptions(), key, &value);
  if (s.IsNotFound()) {
    s = db->Put(leveldb::WriteOptions(), key, url);
    return hashed_url;
  } else if (s.ok()) {
    // std::cout << "Entry was already in Database\n";
    return {};
  } else {
    throw;
  }
}

std::optional<std::string> UrlStorage::find(const UrlId index) const{
  std::array<uint8_t, sizeof(UrlId)> blob;
  num_to_bytes(index, sizeof(index), blob.data());
  leveldb::Slice key((char *)blob.data(), blob.size());
  
  std::string value;
  auto s = db->Get(leveldb::ReadOptions(), key, &value);
  // TODO: handle not found
  if (!s.ok()) {
    std::cerr << "Failed\n";
    return {};
  }
  return value;
}
