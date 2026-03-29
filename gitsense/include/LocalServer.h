#pragma once

#include "ReportGenerator.h"
#include <string>

class LocalServer {
public:
  LocalServer(int port);
  void start();

private:
  int port_;
  std::string getCorsHeaders();
  std::string runAnalysis(const std::string& repoUrl);
};
