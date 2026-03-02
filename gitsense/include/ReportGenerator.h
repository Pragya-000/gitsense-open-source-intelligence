#pragma once
#include "CodeQualityAnalyzer.h"
#include "FileScanner.h"
#include "SecurityAnalyzer.h"
#include <string>


class ReportGenerator {
public:
  ReportGenerator(const FileScanner &fs, const CodeQualityAnalyzer &cqa,
                  const SecurityAnalyzer &sa);
  void generateJsonReport(const std::string &outputPath) const;
  void generatePrettyReport() const;

private:
  const FileScanner &fileScanner;
  const CodeQualityAnalyzer &cqAnalyzer;
  const SecurityAnalyzer &secAnalyzer;
};
