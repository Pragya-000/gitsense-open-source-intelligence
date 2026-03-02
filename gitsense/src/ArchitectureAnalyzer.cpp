#include "ArchitectureAnalyzer.h"
#include <iostream>

ArchitectureAnalyzer::ArchitectureAnalyzer() {}

void ArchitectureAnalyzer::analyze(const std::string &path) {
  std::cout << "[ArchitectureAnalyzer] Analyzing architecture for: " << path
            << "\n";
  // TODO: Detect God objects, cyclic dependencies, etc.
}
