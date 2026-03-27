#pragma once
#include <string>
#include <vector>

struct ArchSmell {
  std::string file;
  std::string type;
  std::string details;
};

class ArchitectureAnalyzer {
public:
  ArchitectureAnalyzer();
  void analyze(const std::vector<std::string> &files);
  const std::vector<ArchSmell>& getSmells() const;

private:
  std::vector<ArchSmell> smells;
};
