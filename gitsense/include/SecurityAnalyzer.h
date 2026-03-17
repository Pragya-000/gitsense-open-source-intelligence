#pragma once
#include <string>
#include <vector>

struct SecurityIssue {
  std::string file;
  int line;
  std::string description;
  std::string severity;
  std::string rawLine;
};

class SecurityAnalyzer {
public:
  SecurityAnalyzer();
  void analyze(const std::vector<std::string> &files);
  const std::vector<SecurityIssue> &getIssues() const;
  int getIssuesCount() const;

private:
  std::vector<SecurityIssue> issues;
  void analyzeFile(const std::string &path);
};
