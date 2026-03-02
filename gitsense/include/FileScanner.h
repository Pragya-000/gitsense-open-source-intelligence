#pragma once
#include <string>
#include <vector>

class FileScanner {
public:
  FileScanner();
  void scan(const std::string &path);

  int getTotalFiles() const;
  int getSourceFilesCount() const;
  int getLinesOfCode() const;
  int getCommentLines() const;
  int getBlankLines() const;

  const std::vector<std::string> &getSourceFiles() const;

private:
  int totalFiles = 0;
  int sourceFilesCount = 0;
  int linesOfCode = 0;
  int commentLines = 0;
  int blankLines = 0;

  std::vector<std::string> sourceFiles;

  bool isSourceFile(const std::string &ext) const;
  void analyzeFile(const std::string &filepath);
};
