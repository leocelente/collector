
#include "../include/database.h"

#include <cassert>
#include <iostream>
#include <optional>

using namespace db;

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
  std::vector<std::string> results(idxs.size());

  for (const auto &idx : idxs) {
    auto url = urls.find(idx);
    if (url) {
      results.push_back(url.value());
    }
  }
  return results;
}

// =============================================================================
