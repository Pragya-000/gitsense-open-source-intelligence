#include "GitHistoryAnalyzer.h"
#include <iostream>

GitHistoryAnalyzer::GitHistoryAnalyzer() {}

void GitHistoryAnalyzer::analyze(const std::string &path) {
  std::cout << "[GitHistoryAnalyzer] Analyzing git history in: " << path
            << "\n";
  // TODO: Connect to git logs, calculate bus factor and top authors
}
