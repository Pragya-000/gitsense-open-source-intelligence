#include "GitHistoryAnalyzer.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <memory>
#include <stdexcept>
#include <array>
#include <sstream>

GitHistoryAnalyzer::GitHistoryAnalyzer() {}

void GitHistoryAnalyzer::analyze(const std::string &path) {
  std::cout << "[GitHistoryAnalyzer] Analyzing git history in: " << path << "\n";
  
  std::string tempFile = ".gitsense_temp.log";
  std::string command = "git -C \"" + path + "\" shortlog -s -n --all > " + tempFile + " 2>nul";
  
  // Wait, if it fails, system() returns non-zero, but we can't reliably rely on it, we just check the file.
  if (std::system(command.c_str()) != 0) {
     // May fail if git is not installed, but checking the file is safer
  }

  std::ifstream inFile(tempFile);
  if (!inFile.is_open()) {
    std::cerr << "[GitHistoryAnalyzer] Warning: failed to parse git history logs.\n";
    return;
  }

  std::stringstream bufferStream;
  bufferStream << inFile.rdbuf();
  std::string result = bufferStream.str();
  
  inFile.close();
  std::remove(tempFile.c_str());

  // Parse the output: typically "    <commits>\t<author name>\n"
  std::stringstream ss(result);
  std::string line;
  while (std::getline(ss, line)) {
    if (line.empty()) continue;
    
    int commits = 0;
    std::string name = "";
    
    // Parse the number
    size_t i = 0;
    while (i < line.size() && (line[i] == ' ' || line[i] == '\t')) i++; // skip whitespace
    
    std::string countStr = "";
    while (i < line.size() && isdigit(line[i])) {
      countStr += line[i];
      i++;
    }
    if (!countStr.empty()) {
      commits = std::stoi(countStr);
    }
    
    // Skip spacing between number and name (usually tab or space)
    while (i < line.size() && (line[i] == ' ' || line[i] == '\t')) i++;
    
    if (i < line.size()) {
       name = line.substr(i);
       // Trim trailing newline/carriage return
       while(!name.empty() && (name.back() == '\r' || name.back() == '\n' || name.back() == ' '))
           name.pop_back();
    }
    
    if (commits > 0 && !name.empty()) {
       topContributors.push_back({name, commits});
       totalCommits += commits;
    }
  }
}

int GitHistoryAnalyzer::getTotalCommits() const {
  return totalCommits;
}

const std::vector<AuthorStat>& GitHistoryAnalyzer::getTopContributors() const {
    return topContributors;
}
