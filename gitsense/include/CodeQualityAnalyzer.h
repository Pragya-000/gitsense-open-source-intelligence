#pragma once
#include <string>
#include <vector>

class CodeQualityAnalyzer {
public:
  CodeQualityAnalyzer();
  void analyze(const std::vector<std::string> &files);
  int getScore() const;
  int getTodos() const;
  int getLongFunctions() const;
  int getLargeFiles() const;

private:
  int score = 100;
  int todosFound = 0;
  int longFunctions = 0;
  int largeFiles = 0;

  void analyzeFile(const std::string &path);
};
