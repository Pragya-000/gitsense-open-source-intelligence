#include "CodeQualityAnalyzer.h"
#include "FileScanner.h"
#include "ReportGenerator.h"
#include "SecurityAnalyzer.h"
#include <iostream>
#include <string>
#include <vector>


void printHelp() {
  std::cout << "GitSense - AI-Powered Open Source Code Intelligence Platform\n";
  std::cout << "Usage:\n";
  std::cout
      << "  gitsense scan <path>                   Scan a local directory\n";
  std::cout
      << "  gitsense scan <path> report --json     Output results as JSON\n";
  std::cout << "  gitsense scan <path> report --pretty   Output pretty "
               "terminal results\n";
  std::cout
      << "  gitsense --help                        Show this help message\n";
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printHelp();
    return 1;
  }

  std::vector<std::string> args(argv + 1, argv + argc);
  std::string command = args[0];

  if (command == "--help" || command == "-h") {
    printHelp();
    return 0;
  }

  // Check if we start with scan
  if (command == "scan") {
    if (args.size() < 2) {
      std::cerr << "Error: 'scan' requires a path.\n";
      return 1;
    }
    std::string target = args[1];
    std::cout << "[INFO] Initializing GitSense scanner for target: " << target
              << "\n\n";

    FileScanner scanner;
    scanner.scan(target);

    CodeQualityAnalyzer cqAnalyzer;
    cqAnalyzer.analyze(scanner.getSourceFiles());

    SecurityAnalyzer secAnalyzer;
    secAnalyzer.analyze(scanner.getSourceFiles());

    ReportGenerator reportGen(scanner, cqAnalyzer, secAnalyzer);

    // Handle trailing report options if provided inline
    if (args.size() > 2 && args[2] == "report") {
      if (args.size() > 3 && args[3] == "--json") {
        std::string out = (args.size() > 4) ? args[4] : "intelligence.json";
        reportGen.generateJsonReport(out);
      } else if (args.size() > 3 && args[3] == "--pretty") {
        reportGen.generatePrettyReport();
      } else {
        reportGen.generatePrettyReport();
      }
    } else {
      // Default to pretty output if they just ran 'scan'
      reportGen.generatePrettyReport();
    }
  } else {
    std::cerr << "Unknown command: " << command << "\n";
    printHelp();
    return 1;
  }

  return 0;
}
