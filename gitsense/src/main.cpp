#include "CodeQualityAnalyzer.h"
#include "FileScanner.h"
#include "ReportGenerator.h"
#include "SecurityAnalyzer.h"
#include "GitHistoryAnalyzer.h"
#include "ArchitectureAnalyzer.h"
#include "LocalServer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


void printHelp() {
  std::cout << "GitSense - AI-Powered Open Source Code Intelligence Platform\n";
  std::cout << "Usage:\n";
  std::cout
      << "  gitsense scan <path>                   Scan a local directory\n";
  std::cout
      << "  gitsense scan <path> report --json     Output results as JSON\n";
  std::cout
      << "  gitsense scan <path> report --pretty   Output pretty "
         "terminal results\n";
  std::cout << "  gitsense serve                     Start the Local Server on port 8080\n";
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

  // Handle serve command
  if (command == "serve") {
    LocalServer server(8080);
    server.start();
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
    SecurityAnalyzer secAnalyzer;
    ArchitectureAnalyzer archAnalyzer;

    std::cout << "[Pipeline] Loading source code directly into RAM for Single-Pass Analysis...\n";
    for (const auto& filePath : scanner.getSourceFiles()) {
        std::ifstream file(filePath);
        if (!file.is_open()) continue;

        std::vector<std::string> lines;
        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }

        cqAnalyzer.analyzeLines(filePath, lines);
        secAnalyzer.analyzeLines(filePath, lines);
        archAnalyzer.analyzeLines(filePath, lines);
    }

    GitHistoryAnalyzer gitAnalyzer;
    gitAnalyzer.analyze(target);

    ReportGenerator reportGen(scanner, cqAnalyzer, secAnalyzer, gitAnalyzer, archAnalyzer);

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
