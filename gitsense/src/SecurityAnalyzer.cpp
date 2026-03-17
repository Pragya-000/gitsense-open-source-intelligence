#include "SecurityAnalyzer.h"
#include <fstream>
#include <iostream>


SecurityAnalyzer::SecurityAnalyzer() {}

void SecurityAnalyzer::analyzeFile(const std::string &path) {
  std::ifstream file(path);
  if (!file.is_open())
    return;

  std::string line;
  int lineNum = 0;

  while (std::getline(file, line)) {
    lineNum++;

    if (line.find("API_KEY") != std::string::npos ||
        line.find("password =") != std::string::npos ||
        line.find("SECRET") != std::string::npos) {
      issues.push_back(
          {path, lineNum, "Possible hardcoded secret detected.", "High", line});
    }

    // Unsafe C functions
    if (line.find("strcpy(") != std::string::npos ||
        line.find("gets(") != std::string::npos ||
        line.find("sprintf(") != std::string::npos) {
      issues.push_back(
          {path, lineNum, "Unsafe C memory function detected.", "Medium", line});
    }

    // Dangerous system calls
    if (line.find("system(") != std::string::npos) {
      issues.push_back({path, lineNum, "Usage of system() call.", "High", line});
    }
  }
}

void SecurityAnalyzer::analyze(const std::vector<std::string> &files) {
  std::cout << "[SecurityAnalyzer] Analyzing security patterns...\n";
  for (const auto &f : files) {
    analyzeFile(f);
  }
}

const std::vector<SecurityIssue> &SecurityAnalyzer::getIssues() const {
  return issues;
}

int SecurityAnalyzer::getIssuesCount() const { return issues.size(); }
