#include "CodeQualityAnalyzer.h"
#include <iostream>

CodeQualityAnalyzer::CodeQualityAnalyzer() {}

void CodeQualityAnalyzer::analyzeLines(const std::string &path, const std::vector<std::string> &lines) {
  int lineCount = 0;
  int currentFunctionLength = 0;
  int braceDepth = 0;

  for (const auto& line : lines) {
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

int CodeQualityAnalyzer::getScore() const { return (score < 0) ? 0 : score; }
int CodeQualityAnalyzer::getTodos() const { return todosFound; }
int CodeQualityAnalyzer::getLongFunctions() const { return longFunctions; }
int CodeQualityAnalyzer::getLargeFiles() const { return largeFiles; }
