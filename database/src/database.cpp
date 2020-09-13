
#include "../include/database.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <optional>

using namespace db;

bool Database::add(const std::string &url,
                   const std::vector<std::string> &tokens) const {
  const auto index = this->urls.add(url);
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
  return true;
}

std::vector<std::string> Database::find(const std::string &token) const {
  const auto idxs = indexes.find(token);
  std::vector<std::string> results(idxs.size());
  std::transform(idxs.begin(), idxs.end(), results.begin(),
                 [&](const auto &idx) {
                   auto url = urls.find(idx);
                   if (url) {
                     return url.value();
                   } else {
                     return std::string{"no match"};
                   }
                 });

  return results;
}
