#pragma once
#include <string>

class RepoAssistantEngine {
public:
  RepoAssistantEngine();
  std::string askQuestion(const std::string& repoJsonContext, const std::string& question);
};
