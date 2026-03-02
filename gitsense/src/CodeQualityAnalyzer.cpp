#include "CodeQualityAnalyzer.h"
#include <fstream>
#include <iostream>


CodeQualityAnalyzer::CodeQualityAnalyzer() {}

void CodeQualityAnalyzer::analyzeFile(const std::string &path) {
  std::ifstream file(path);
  if (!file.is_open())
    return;

  std::string line;
  int lineCount = 0;
  int currentFunctionLength = 0;
  int braceDepth = 0;

  while (std::getline(file, line)) {
    lineCount++;

    if (line.find("TODO") != std::string::npos ||
        line.find("FIXME") != std::string::npos) {
      todosFound++;
      score--;
    }

    // Simple brace heuristic for function length
    for (char c : line) {
      if (c == '{')
        braceDepth++;
      else if (c == '}') {
        if (braceDepth == 1 && currentFunctionLength > 50) {
          longFunctions++;
          score -= 2;
        }
        if (braceDepth > 0)
          braceDepth--;
        if (braceDepth == 0)
          currentFunctionLength = 0;
      }
    }
    if (braceDepth > 0) {
      currentFunctionLength++;
    }
  }

  if (lineCount > 500) {
    largeFiles++;
    score -= 5;
  }
}

void CodeQualityAnalyzer::analyze(const std::vector<std::string> &files) {
  std::cout << "[CodeQualityAnalyzer] Analyzing " << files.size()
            << " files for code quality...\n";
  for (const auto &f : files) {
    analyzeFile(f);
  }
  if (score < 0)
    score = 0;
}

int CodeQualityAnalyzer::getScore() const { return score; }
int CodeQualityAnalyzer::getTodos() const { return todosFound; }
int CodeQualityAnalyzer::getLongFunctions() const { return longFunctions; }
int CodeQualityAnalyzer::getLargeFiles() const { return largeFiles; }
