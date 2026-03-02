#pragma once
#include <string>

class LanguageDetector {
public:
  LanguageDetector();
  std::string detectPrimaryLanguage(const std::string &path);
};
