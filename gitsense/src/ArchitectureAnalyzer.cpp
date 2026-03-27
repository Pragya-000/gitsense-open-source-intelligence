#include "ArchitectureAnalyzer.h"
#include <iostream>

ArchitectureAnalyzer::ArchitectureAnalyzer() {}

void ArchitectureAnalyzer::analyzeLines(const std::string &path, const std::vector<std::string> &lines) {
  int lineCount = 0;
  int includeCount = 0;

  for (const auto& line : lines) {
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

const std::vector<ArchSmell>& ArchitectureAnalyzer::getSmells() const {
  return smells;
}
