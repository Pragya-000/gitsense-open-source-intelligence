#include "ArchitectureAnalyzer.h"
#include <iostream>
#include <fstream>

ArchitectureAnalyzer::ArchitectureAnalyzer() {}

void ArchitectureAnalyzer::analyze(const std::vector<std::string> &files) {
  std::cout << "[ArchitectureAnalyzer] Analyzing architecture for God Objects and Tight Coupling...\n";

  for (const auto &path : files) {
    std::ifstream file(path);
    if (!file.is_open()) continue;

    std::string line;
    int lineCount = 0;
    int includeCount = 0;

    while (std::getline(file, line)) {
      lineCount++;
      // Count includes and module imports
      if (line.find("#include") != std::string::npos || 
          line.find("import ") != std::string::npos ||
          line.find("require(") != std::string::npos) {
        includeCount++;
      }
    }

    if (lineCount > 500) {
      smells.push_back({path, "God Object", "File exceeds 500 lines (" + std::to_string(lineCount) + " lines)."});
    }

    if (includeCount > 12) {
      smells.push_back({path, "Tight Coupling", "Unusually high number of dependencies (" + std::to_string(includeCount) + " includes/imports)."});
    }
  }
}

const std::vector<ArchSmell>& ArchitectureAnalyzer::getSmells() const {
  return smells;
}
