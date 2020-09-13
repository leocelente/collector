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
    std::cout << "URL was already in database...\n";
    return true;
  }
  std::cout << "Saving URL\n";
  for (const auto token : tokens) {
    auto ok = this->indexes.add(token, index.value());
    if (!ok) {
      return false;
    }
  }
  auto results = indexes.find(tokens[0]);
  for (const auto &r : results) {
    std::cout << r << '\n';
  }
  return true;
}

std::vector<std::string> Database::find(std::string token) {
  auto idxs = indexes.find(token);
  for (const auto &idx : idxs) {
    // TODO: get url from index
    auto url = urls.find(idx);
    if (url) {
      std::cout << "entry: " << url.value() << '\n';
    }
  }
  return {};
}

InvIndexStorage::InvIndexStorage() {
  std::cout << "Starting InvIndex Storage\n";
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

// =============================================================================

UrlStorage::UrlStorage() {
  std::cout << "Starting Url Storage\n";
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
  std::cout << "HASH: '" << hashed_url << "'\n";

  uint8_t blob[8] = {0xDE, 0xAD, 0xBE, 0xEF, 0xDE, 0xAD, 0xBE, 0xEF};
  num_to_bytes(hashed_url, sizeof(hashed_url), blob);
  // TODO: Find better solution for this conversion
  leveldb::Slice key2((char *)blob, 8);

  auto s = db->Get(leveldb::ReadOptions(), key2, &value);
  if (s.IsNotFound()) {
    std::cout << "Writing value\n";
    s = db->Put(leveldb::WriteOptions(), key2, url);
  } else if (s.ok()) {
    std::cout << "Entry was already in Database\n";
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
