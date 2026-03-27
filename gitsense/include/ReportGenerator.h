#pragma once
#include "CodeQualityAnalyzer.h"
#include "FileScanner.h"
#include "SecurityAnalyzer.h"
#include "GitHistoryAnalyzer.h"
#include "ArchitectureAnalyzer.h"
#include <string>


class ReportGenerator {
public:
  ReportGenerator(const FileScanner &fs, const CodeQualityAnalyzer &cqa,
                  const SecurityAnalyzer &sa, const GitHistoryAnalyzer &gha,
                  const ArchitectureAnalyzer &aa);
  void generateJsonReport(const std::string &outputPath) const;
  void generatePrettyReport() const;

private:
  const FileScanner &fileScanner;
  const CodeQualityAnalyzer &cqAnalyzer;
  const SecurityAnalyzer &secAnalyzer;
  const GitHistoryAnalyzer &gitAnalyzer;
  const ArchitectureAnalyzer &archAnalyzer;
};
