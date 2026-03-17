#include <iostream>
#include <string>
#include <vector>

// Helper function to replace all occurrences of a substring
void replaceAll(std::string& source, const std::string& from, const std::string& to) {
    if(from.empty()) return;
    size_t start_pos = 0;
    while((start_pos = source.find(from, start_pos)) != std::string::npos) {
        source.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

// AI auto-remediation mock for hackathon demo
std::string generateSaferCode(std::string vulnerableCode) {
    std::string fixedCode = vulnerableCode;

    // 1. Buffer Overflow: strcpy -> strncpy
    // Note: This naive replacement assumes a destination buffer size 
    // is known or defaults to a safe max for demo purposes.
    // In a real AI, determining `sizeof(dest)` requires deeper AST analysis.
    replaceAll(fixedCode, "strcpy(", "strncpy(");
    
    // Often `strcpy(dest, src)` becomes `strncpy(dest, src, sizeof(dest))` 
    // Since we're parsing raw strings, we just visually show the intent:
    // We'll replace the closing paren of strncpy lines to show a dummy size constraint
    // (A bit complex for regex, so we just swapped the name above).

    // 2. Unbounded Input: gets -> fgets
    // `gets(buffer);` -> `fgets(buffer, sizeof(buffer), stdin);`
    size_t getsPos = fixedCode.find("gets(");
    if (getsPos != std::string::npos) {
        size_t endParen = fixedCode.find(")", getsPos);
        if (endParen != std::string::npos) {
            std::string bufferName = fixedCode.substr(getsPos + 5, endParen - (getsPos + 5));
            std::string secureGets = "fgets(" + bufferName + ", sizeof(" + bufferName + "), stdin)";
            
            // Reconstruct the string
            fixedCode = fixedCode.substr(0, getsPos) + secureGets + fixedCode.substr(endParen + 1);
        }
    }

    // 3. Command Injection: system -> exec / warning
    // For a demo, replacing `system("...")` with a commented-out warning is a great talking point
    size_t systemPos = fixedCode.find("system(");
    if (systemPos != std::string::npos) {
         replaceAll(fixedCode, "system(", "// [AI FIX] WARN: Dangerous system() call detected. Replaced with safe stub.\n    // system(");
    }
    
    // 4. Broken Crypto: md5 -> sha256
    replaceAll(fixedCode, "MD5(", "SHA256(");

    return fixedCode;
}

// --- Example Usage ---
int main() {
    std::string badCode = R"(
void processInput() {
    char buffer[256];
    char input[512];
    
    gets(buffer);
    strcpy(input, buffer);
    
    system("rm -rf /");
    
    std::string hash = MD5(input);
}
)";

    std::cout << "--- VULNERABLE CODE ---\n" << badCode << "\n";
    std::cout << "--- AI REMEDIATED CODE ---\n" << generateSaferCode(badCode) << "\n";

    return 0;
}
