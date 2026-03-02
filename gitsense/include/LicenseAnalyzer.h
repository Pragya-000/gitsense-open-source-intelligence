#pragma once
#include <string>

class LicenseAnalyzer {
public:
  LicenseAnalyzer();
  std::string detectLicense(const std::string &path);
};
