#include "SecurityAnalyzer.h"
#include <iostream>

SecurityAnalyzer::SecurityAnalyzer() {}

void SecurityAnalyzer::analyzeLines(const std::string &path, const std::vector<std::string> &lines) {
  int lineNum = 0;

  for (const auto& line : lines) {
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

const std::vector<SecurityIssue> &SecurityAnalyzer::getIssues() const {
  return issues;
}

int SecurityAnalyzer::getIssuesCount() const { return issues.size(); }
