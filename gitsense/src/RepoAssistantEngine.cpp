#include "RepoAssistantEngine.h"
#include <algorithm>
#include <cctype>

RepoAssistantEngine::RepoAssistantEngine() {}

std::string RepoAssistantEngine::askQuestion(const std::string& repoJsonContext, const std::string& question) {
    std::string q = question;
    std::transform(q.begin(), q.end(), q.begin(), ::tolower);

    if (q.find("security") != std::string::npos || q.find("vulnerabilit") != std::string::npos) {
        if (repoJsonContext.find("\"security_issues\": []") != std::string::npos) {
            return "Based on my analysis, the repository looks secure. I did not find any major security issues.";
        } else {
            return "I detected some security vulnerabilities. Please check the JSON report. I recommend using strncpy instead of strcpy and reviewing system() calls.";
        }
    }
    
    if (q.find("architecture") != std::string::npos || q.find("smell") != std::string::npos) {
        if (repoJsonContext.find("architecture_smells\": []") != std::string::npos) {
            return "The architecture seems fine with no major God objects or tight coupling detected.";
        } else {
            return "There are some architecture smells, such as large files or God objects. You should consider refactoring these dense modules.";
        }
    }

    if (q.find("quality") != std::string::npos || q.find("todo") != std::string::npos) {
        return "The code quality score reflects the number of long functions, TODOs, and large files. Try completing the TODOs to improve the score.";
    }

    if (q.find("commit") != std::string::npos || q.find("contributor") != std::string::npos) {
        return "I have analyzed the git history. The git_history section in the report lists the top contributors and commit counts. A healthy bus factor is important.";
    }

    return "I am a local AI assistant. Based on the GitSense analysis, I can help you understand security, architecture, quality, or git metrics of this repo.";
}
