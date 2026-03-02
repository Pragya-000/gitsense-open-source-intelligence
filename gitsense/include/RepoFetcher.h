#pragma once
#include <string>

class RepoFetcher {
public:
  RepoFetcher();
  bool fetch(const std::string &target);
};
