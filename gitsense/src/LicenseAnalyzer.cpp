#include "LicenseAnalyzer.h"
#include <iostream>

LicenseAnalyzer::LicenseAnalyzer() {}

std::string LicenseAnalyzer::detectLicense(const std::string &path) {
  std::cout << "[LicenseAnalyzer] Detecting license in: " << path << "\n";
  // TODO: Detect license signatures and check SPDX tags
  return "Unknown";
}
