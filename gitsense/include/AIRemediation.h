#pragma once
#include <string>

class AIRemediation {
public:
    static std::string generateSaferCode(const std::string& vulnerableCode);
private:
    static void replaceAll(std::string& source, const std::string& from, const std::string& to);
};
