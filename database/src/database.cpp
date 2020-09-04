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

std::optional<UrlId> UrlStorage::add(const std::string url) {
  UrlId id = 1;
  std::cout << "Saving URL: " << url << " with id: " << id << '\n';
  leveldb::Slice key1 = "0xDEAD";
  std::string value;
  leveldb::Status s = db->Put(leveldb::WriteOptions(), key1, "beef");
  if (s.ok()) {
    s = db->Get(leveldb::ReadOptions(), key1, &value);
  }
  if (s.ok()) {
	std::cout << key1.ToString() << ": '" << value << "'\n"; 
    s = db->Delete(leveldb::WriteOptions(), key1);
  }
  return 1;
}
