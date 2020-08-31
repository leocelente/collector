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
    std::cout << "Addding Token to InvIndexStorage\n";
    auto ok = this->indexes.add(token, index.value());
    if(!ok) {
      return false;
    }
  }
  return true;
}

InvIndexStorage::InvIndexStorage() {
  std::cout << "Starting InvIndex Storage" << std::endl;
}

bool InvIndexStorage::add(std::string token, UrlId id) {
  std::cout << "Addding token: " << token << "to id: " << id;
  return true;
}

UrlStorage::UrlStorage() { std::cout << "Starting Url Storage" << std::endl; }

std::optional<UrlId> UrlStorage::add(const std::string url) {
  UrlId id = 1;
  std::cout << "Saving URL: " << url << " with hash: " << id << '\n';
  return 1;
}
