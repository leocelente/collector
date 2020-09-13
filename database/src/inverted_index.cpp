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

bool InvIndexStorage::add(std::string token, UrlId id) {
  std::cout << "Addding token: '" << token << "' to id: " << id << '\n';

  // TODO: get index
  leveldb::Slice key{token};
  std::string value;

  std::array<uint8_t, 8> index_arr;
  num_to_bytes(id, 8, index_arr.data());

  auto s = db->Get(leveldb::ReadOptions(), key, &value);
  if (s.ok()) {
    // TODO: copy contents
    std::vector<char> new_value(value.size());
    std::copy(value.begin(), value.end(), new_value.begin());
    // TODO: mutate

    for (const auto &c : index_arr) {
      new_value.push_back(c);
    }
    // TODO: write
    leveldb::Slice val((char *)new_value.data(), new_value.size());
    s = db->Put(leveldb::WriteOptions(), key, val);
    if (!s.ok()) {
      std::cerr << "Failed at write\n";
    }
  } else if (s.IsNotFound()) {
    // create it
    leveldb::Slice val((char *)index_arr.data(), index_arr.size());
    s = db->Put(leveldb::WriteOptions(), key, val);
    if (!s.ok()) {
      std::cerr << "Failed at write\n";
    }
  } else {
    throw;
  }

  return true;
}

std::vector<UrlId> InvIndexStorage::find(std::string token) {
  leveldb::Slice key{token};
  std::vector<UrlId> idxs;
  std::string read_val;
  auto s = db->Get(leveldb::ReadOptions(), key, &read_val);
  std::vector<uint8_t> data(read_val.size());
  std::copy(read_val.begin(), read_val.end(), data.begin());
  if (s.ok()) {
    int n = data.size();
    for (int i = 0; i < n; i += 8) {
      uint64_t x = bytes_to_num(8, &data[i]);
      idxs.push_back(x);
    }
  }
  return idxs;
}
