#include "AIRemediation.h"

void AIRemediation::replaceAll(std::string& source, const std::string& from, const std::string& to) {
    if(from.empty()) return;
    size_t start_pos = 0;
    while((start_pos = source.find(from, start_pos)) != std::string::npos) {
        source.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

std::string AIRemediation::generateSaferCode(const std::string& vulnerableCode) {
    std::string fixedCode = vulnerableCode;

    replaceAll(fixedCode, "strcpy(", "strncpy(");
    
    size_t getsPos = fixedCode.find("gets(");
    if (getsPos != std::string::npos) {
        size_t endParen = fixedCode.find(")", getsPos);
        if (endParen != std::string::npos) {
            std::string bufferName = fixedCode.substr(getsPos + 5, endParen - (getsPos + 5));
            std::string secureGets = "fgets(" + bufferName + ", sizeof(" + bufferName + "), stdin)";
            fixedCode = fixedCode.substr(0, getsPos) + secureGets + fixedCode.substr(endParen + 1);
        }
    }

    size_t systemPos = fixedCode.find("system(");
    if (systemPos != std::string::npos) {
         replaceAll(fixedCode, "system(", "// [AI FIX] WARN: Dangerous system() call detected. Replaced with safe stub.\n    // system(");
    }
    
    replaceAll(fixedCode, "MD5(", "SHA256(");

    return fixedCode;
}
