#pragma once
#include <string>

class GitHistoryAnalyzer {
public:
  GitHistoryAnalyzer();
  void analyze(const std::string &path);
};
