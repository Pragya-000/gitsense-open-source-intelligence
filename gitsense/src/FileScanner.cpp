#include "FileScanner.h"
#include <algorithm>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <sys/stat.h>

FileScanner::FileScanner() {}

bool FileScanner::isSourceFile(const std::string &ext) const {
  static const std::vector<std::string> exts = {
      ".cpp", ".c", ".h", ".hpp", ".py", ".java", ".js", ".ts", ".go"};
  return std::find(exts.begin(), exts.end(), ext) != exts.end();
}

void FileScanner::analyzeFile(const std::string &filepath) {
  std::ifstream file(filepath);
  if (!file.is_open())
    return;

  std::string line;
  while (std::getline(file, line)) {
    linesOfCode++;

    // Simple trim for blank/comment check
    size_t start = line.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) {
      blankLines++;
    } else if (line.compare(start, 2, "//") == 0 ||
               line.compare(start, 1, "#") == 0) {
      commentLines++; // A simplistic heuristic for comments
    }
  }
}

void FileScanner::scan(const std::string &path) {
  std::cout << "[FileScanner] Scanning directory: " << path << "\n";
  DIR *dir;
  struct dirent *ent;
  if ((dir = opendir(path.c_str())) != NULL) {
    while ((ent = readdir(dir)) != NULL) {
      std::string name = ent->d_name;
      if (name == "." || name == ".." || name == ".git" || name == ".vscode" || name == "build" || name == "node_modules")
        continue;

      std::string fullPath = path + "/" + name;

      struct stat st;
      if (stat(fullPath.c_str(), &st) == 0) {
        if (S_ISDIR(st.st_mode)) {
          scan(fullPath);
        } else if (S_ISREG(st.st_mode)) {
          totalFiles++;
          size_t pos = name.find_last_of(".");
          if (pos != std::string::npos) {
            std::string ext = name.substr(pos);
            if (isSourceFile(ext)) {
              sourceFilesCount++;
              sourceFiles.push_back(fullPath);
              analyzeFile(fullPath);
            }
          }
        }
      }
    }
    closedir(dir);
  } else {
    std::cerr << "Error: Could not open directory " << path << "\n";
  }
}

int FileScanner::getTotalFiles() const { return totalFiles; }
int FileScanner::getSourceFilesCount() const { return sourceFilesCount; }
int FileScanner::getLinesOfCode() const { return linesOfCode; }
int FileScanner::getCommentLines() const { return commentLines; }
int FileScanner::getBlankLines() const { return blankLines; }
const std::vector<std::string> &FileScanner::getSourceFiles() const {
  return sourceFiles;
}
