#pragma once
#include <string>

class DependencyAnalyzer {
public:
  DependencyAnalyzer();
  void analyze(const std::string &path);
};
