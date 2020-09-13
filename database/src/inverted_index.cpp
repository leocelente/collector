#include "../include/inverted_index.h"
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

InvIndexStorage::InvIndexStorage() {
  leveldb::Options options;
  options.create_if_missing = true;
  leveldb::Status status =
      leveldb::DB::Open(options, "/tmp/invidxdb", &(this->db));
  assert(status.ok());
}

InvIndexStorage::~InvIndexStorage() { delete db; }

bool InvIndexStorage::add(const std::string& token, const UrlId id) const {
  std::cout << "Addding token: '" << token <<'\n';

  leveldb::Slice key{token};
  std::string value;

  std::array<uint8_t, 8> index_arr;
  num_to_bytes(id, 8, index_arr.data());

  auto s = db->Get(leveldb::ReadOptions(), key, &value);
  if (s.ok()) {
    std::vector<char> new_value(value.size());
    std::copy(value.begin(), value.end(), new_value.begin());
    std::copy(index_arr.begin(), index_arr.end(), new_value.begin());

    leveldb::Slice new_val_slice((char *)new_value.data(), new_value.size());
    s = db->Put(leveldb::WriteOptions(), key, new_val_slice);
    if (!s.ok()) {
      std::cerr << "Could not rewrite value\n";
      return false;
    }
  } else if (s.IsNotFound()) {
    leveldb::Slice val((char *)index_arr.data(), index_arr.size());
    s = db->Put(leveldb::WriteOptions(), key, val);
    if (!s.ok()) {
      std::cerr << "Could not write new value\n";
      return false;
    }
  } else {
    throw;
  }
  return true;
}

std::vector<UrlId> InvIndexStorage::find(const std::string& token) const {
  std::vector<UrlId> idxs;
  std::string read_val;
  auto s = db->Get(leveldb::ReadOptions(), token, &read_val);
  std::vector<uint8_t> data(read_val.size());
  std::copy(read_val.begin(), read_val.end(), data.begin());
  if (s.ok()) {
    const auto n = data.size();
    for (size_t i = 0; i < n; i += 8) {
      const auto x = bytes_to_num(8, &data[i]);
      idxs.push_back(x);
    }
  }
  return idxs;
}
