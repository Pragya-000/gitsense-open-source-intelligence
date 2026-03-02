#include "LanguageDetector.h"
#include <iostream>

LanguageDetector::LanguageDetector() {}

std::string LanguageDetector::detectPrimaryLanguage(const std::string &path) {
  std::cout << "[LanguageDetector] Detecting language for: " << path << "\n";
  // TODO: Implement extension-based or file-signature based language detection
  return "Unknown";
}
