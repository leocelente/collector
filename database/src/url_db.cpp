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

std::optional<UrlId> UrlStorage::add(const std::string url) {
  std::string value;
  std::hash<std::string> hasher;
  uint64_t hashed_url = hasher(url);
  //   std::cout << "HASH: '" << hashed_url << "'\n";

  uint8_t blob[8] = {0xDE, 0xAD, 0xBE, 0xEF, 0xDE, 0xAD, 0xBE, 0xEF};
  num_to_bytes(hashed_url, sizeof(hashed_url), blob);
  // TODO: Find better solution for this conversion
  leveldb::Slice key2((char *)blob, 8);

  auto s = db->Get(leveldb::ReadOptions(), key2, &value);
  if (s.IsNotFound()) {
    std::cout << "Writing value\n";
    s = db->Put(leveldb::WriteOptions(), key2, url);
  } else if (s.ok()) {
    // std::cout << "Entry was already in Database\n";
    return {};
  } else {
    throw;
  }
  // ? Checks
  // s = db->Get(leveldb::ReadOptions(), key2, &value);
  // std::cout << "Value should now be: '" << value << "'\n";
  return hashed_url;
}

std::optional<std::string> UrlStorage::find(UrlId index) {
  std::array<uint8_t, 8> blob;
  std::string value;
  num_to_bytes(index, sizeof(index), blob.data());
  leveldb::Slice key((char *)blob.data(), 8);
  auto s = db->Get(leveldb::ReadOptions(), key, &value);
  // TODO: handle not found
  if (!s.ok()) {
    std::cerr << "Failed\n";
    return {};
  }
  return value;
}