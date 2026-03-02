#include "RepoFetcher.h"
#include <iostream>

RepoFetcher::RepoFetcher() {}

bool RepoFetcher::fetch(const std::string &target) {
  std::cout << "[RepoFetcher] Fetching repository: " << target << "\n";
  // TODO: Implement actual git clone or local folder verification
  return true;
}
