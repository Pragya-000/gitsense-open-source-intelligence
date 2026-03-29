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
    }

    // Simple brace heuristic for function length
    for (char c : line) {
      if (c == '{')
        braceDepth++;
      else if (c == '}') {
        if (braceDepth == 1 && currentFunctionLength > 50) {
          longFunctions++;
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
  }
  
  totalLines += lineCount;
  totalFiles++;
}

int CodeQualityAnalyzer::getScore() const { 
  if (totalLines == 0 || totalFiles == 0) return 100;
  
  // Predictable ratios instead of absolute subtraction
  float todoPenalty = (static_cast<float>(todosFound) / totalLines) * 500.0f;
  float funcPenalty = (static_cast<float>(longFunctions) / totalLines) * 2000.0f;
  float filePenalty = (static_cast<float>(largeFiles) / totalFiles) * 50.0f;
  
  int finalScore = 100 - static_cast<int>(todoPenalty + funcPenalty + filePenalty);
  if (finalScore < 0) return 0;
  if (finalScore > 100) return 100;
  return finalScore;
}
int CodeQualityAnalyzer::getTodos() const { return todosFound; }
int CodeQualityAnalyzer::getLongFunctions() const { return longFunctions; }
int CodeQualityAnalyzer::getLargeFiles() const { return largeFiles; }
