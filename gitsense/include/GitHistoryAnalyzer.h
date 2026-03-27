#pragma once
#include <string>
#include <vector>

struct AuthorStat {
  std::string name;
  int commits;
};

class GitHistoryAnalyzer {
public:
  GitHistoryAnalyzer();
  void analyze(const std::string &path);

  int getTotalCommits() const;
  const std::vector<AuthorStat>& getTopContributors() const;

private:
  int totalCommits = 0;
  std::vector<AuthorStat> topContributors;
};
