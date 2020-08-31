#include "../include/database.h"
#include <cassert>
#include <iostream>
#include <leveldb/db.h>
#include <optional>
using namespace db;
Database::Database() {
  std::cout << "Starting Database Service\n";
}

InvIndexStorage::InvIndexStorage() {
  std::cout << "Starting InvIndex Storage" << std::endl;
}

bool InvIndexStorage::add(std::string token, UrlId id) {
  std::cout << "Addding token: " << token << "to id: " << id;
  return true;
}

UrlStorage::UrlStorage(){
  std::cout << "Starting Url Storage" << std::endl;
}

std::optional<UrlId> UrlStorage::add(const std::string url) {
  UrlId id = 1;
  std::cout << "Saving URL: " << url << "with hash: " << id << '\n';
  return 1;
}
