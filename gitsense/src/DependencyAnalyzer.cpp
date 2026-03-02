#include "DependencyAnalyzer.h"
#include <iostream>

DependencyAnalyzer::DependencyAnalyzer() {}

void DependencyAnalyzer::analyze(const std::string &path) {
  std::cout << "[DependencyAnalyzer] Analyzing dependencies in: " << path
            << "\n";
  // TODO: Parse package.json, CMakeLists.txt, requirements.txt, calculate risk
}
