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
  void analyzeLines(const std::string &path, const std::vector<std::string> &lines);
  const std::vector<SecurityIssue> &getIssues() const;
  int getIssuesCount() const;

private:
  std::vector<SecurityIssue> issues;
};
