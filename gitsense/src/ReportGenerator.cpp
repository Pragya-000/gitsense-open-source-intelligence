#include "AIRemediation.h"
#include "ReportGenerator.h"
#include <fstream>
#include <iostream>

ReportGenerator::ReportGenerator(const FileScanner &fs,
                                 const CodeQualityAnalyzer &cqa,
                                 const SecurityAnalyzer &sa,
                                 const GitHistoryAnalyzer &gha)
    : fileScanner(fs), cqAnalyzer(cqa), secAnalyzer(sa), gitAnalyzer(gha) {}

void ReportGenerator::generateJsonReport(const std::string &outputPath) const {
  std::cout << "[ReportGenerator] Writing JSON report to " << outputPath
            << "\n";
  std::ofstream out(outputPath);
  if (!out.is_open())
    return;

  out << "{\n";
  out << "  \"metrics\": {\n";
  out << "    \"total_files\": " << fileScanner.getTotalFiles() << ",\n";
  out << "    \"source_files\": " << fileScanner.getSourceFilesCount() << ",\n";
  out << "    \"lines_of_code\": " << fileScanner.getLinesOfCode() << ",\n";
  out << "    \"code_quality_score\": " << cqAnalyzer.getScore() << "\n";
  out << "  },\n";

  out << "  \"git_history\": {\n";
  out << "    \"total_commits\": " << gitAnalyzer.getTotalCommits() << ",\n";
  out << "    \"top_contributors\": [\n";
  const auto &contributors = gitAnalyzer.getTopContributors();
  for (size_t i = 0; i < contributors.size(); ++i) {
    out << "      {\n";
    out << "        \"name\": \"" << contributors[i].name << "\",\n";
    out << "        \"commits\": " << contributors[i].commits << "\n";
    out << "      }" << (i < contributors.size() - 1 ? "," : "") << "\n";
  }
  out << "    ]\n";
  out << "  },\n";

  out << "  \"security_issues\": [\n";
  const auto &issues = secAnalyzer.getIssues();
  for (size_t i = 0; i < issues.size(); ++i) {
    out << "    {\n";
    out << "      \"file\": \"" << issues[i].file << "\",\n";
    out << "      \"line\": " << issues[i].line << ",\n";
    out << "      \"description\": \"" << issues[i].description << "\",\n";
    out << "      \"severity\": \"" << issues[i].severity << "\",\n";
    
    std::string safeLine = AIRemediation::generateSaferCode(issues[i].rawLine);
    out << "      \"ai_remediation\": \"" << safeLine << "\"\n";
    out << "    }" << (i < issues.size() - 1 ? "," : "") << "\n";
  }
  out << "  ]\n";
  out << "}\n";
  out.close();
}

void ReportGenerator::generatePrettyReport() const {
  std::cout << "\n================================================\n";
  std::cout << "        GitSense Intelligence Report\n";
  std::cout << "================================================\n";
  std::cout << "Files Scanned: " << fileScanner.getTotalFiles() << "\n";
  std::cout << "Source Files:  " << fileScanner.getSourceFilesCount() << "\n";
  std::cout << "Lines of Code: " << fileScanner.getLinesOfCode() << "\n";
  std::cout << "------------------------------------------------\n";
  std::cout << "Top Contributors:\n";
  const auto &contributors = gitAnalyzer.getTopContributors();
  for(const auto& c : contributors) {
      std::cout << "  - " << c.name << " (" << c.commits << " commits)\n";
  }
  if (contributors.empty()) {
      std::cout << "  (No git history found)\n";
  }
  std::cout << "------------------------------------------------\n";
  std::cout << "Code Quality Score: " << cqAnalyzer.getScore() << "/100\n";
  std::cout << "  - TODOs Found: " << cqAnalyzer.getTodos() << "\n";
  std::cout << "  - Long Functions: " << cqAnalyzer.getLongFunctions() << "\n";
  std::cout << "  - Large Files: " << cqAnalyzer.getLargeFiles() << "\n";
  std::cout << "------------------------------------------------\n";
  std::cout << "Security Issues Found: " << secAnalyzer.getIssuesCount()
            << "\n";
  for (const auto &issue : secAnalyzer.getIssues()) {
    std::cout << "  [" << issue.severity << "] " << issue.file << ":"
              << issue.line << " -> " << issue.description << "\n";
    
    std::string safeCode = AIRemediation::generateSaferCode(issue.rawLine);
    // Trim leading whitespaces for clean terminal output
    safeCode.erase(0, safeCode.find_first_not_of(" \t\r\n")); 
    std::cout << "      ✨ AI Suggestion: " << safeCode << "\n";
  }
  std::cout << "================================================\n\n";
}
