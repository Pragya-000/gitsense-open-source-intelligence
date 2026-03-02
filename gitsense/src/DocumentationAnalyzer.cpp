#include "DocumentationAnalyzer.h"
#include <iostream>

DocumentationAnalyzer::DocumentationAnalyzer() {}

void DocumentationAnalyzer::analyze(const std::string &path) {
  std::cout << "[DocumentationAnalyzer] Analyzing documentation in: " << path
            << "\n";
  // TODO: Detect README.md, LICENSE, CONTRIBUTING.md, and code comments ratio
}
