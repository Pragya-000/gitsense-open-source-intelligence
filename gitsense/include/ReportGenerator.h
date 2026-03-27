#pragma once
#include "CodeQualityAnalyzer.h"
#include "FileScanner.h"
#include "SecurityAnalyzer.h"
#include "GitHistoryAnalyzer.h"
#include <string>


class ReportGenerator {
public:
  ReportGenerator(const FileScanner &fs, const CodeQualityAnalyzer &cqa,
                  const SecurityAnalyzer &sa, const GitHistoryAnalyzer &gha);
  void generateJsonReport(const std::string &outputPath) const;
  void generatePrettyReport() const;

private:
  const FileScanner &fileScanner;
  const CodeQualityAnalyzer &cqAnalyzer;
  const SecurityAnalyzer &secAnalyzer;
  const GitHistoryAnalyzer &gitAnalyzer;
};
