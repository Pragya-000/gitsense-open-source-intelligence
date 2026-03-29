#include "LocalServer.h"
#include "RepoFetcher.h"
#include "FileScanner.h"
#include "CodeQualityAnalyzer.h"
#include "SecurityAnalyzer.h"
#include "ArchitectureAnalyzer.h"
#include "GitHistoryAnalyzer.h"
#include "ReportGenerator.h"
#include "RepoAssistantEngine.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#endif

std::string extractJsonStr(const std::string& json, const std::string& key) {
    std::string searchKey = "\"" + key + "\":";
    size_t pos = json.find(searchKey);
    if (pos == std::string::npos) return "";
    pos += searchKey.length();
    while (pos < json.length() && (json[pos] == ' ' || json[pos] == '\t' || json[pos] == '\n' || json[pos] == '\r')) pos++;
    
    if (pos < json.length() && json[pos] == '\"') {
        size_t endPos = json.find('\"', pos + 1);
        if (endPos != std::string::npos) return json.substr(pos + 1, endPos - pos - 1);
    }
    return "";
}

LocalServer::LocalServer(int port) : port_(port) {}

std::string LocalServer::runAnalysis(const std::string& repoUrl) {
    std::string targetDir = "gitsense_repo_cache";
    std::string rmCmd = "rmdir /s /q " + targetDir + " >nul 2>&1";
    system(rmCmd.c_str());
    
    std::string cloneCmd = "git clone " + repoUrl + " " + targetDir;
    int res = system(cloneCmd.c_str());
    if (res != 0 && repoUrl.find("http") == std::string::npos) {
        targetDir = repoUrl;
    }

    FileScanner scanner;
    scanner.scan(targetDir);

    CodeQualityAnalyzer cqAnalyzer;
    SecurityAnalyzer secAnalyzer;
    ArchitectureAnalyzer archAnalyzer;

    for (const auto& filePath : scanner.getSourceFiles()) {
        std::ifstream file(filePath);
        if (!file.is_open()) continue;
        std::vector<std::string> lines;
        std::string line;
        while (std::getline(file, line)) lines.push_back(line);

        cqAnalyzer.analyzeLines(filePath, lines);
        secAnalyzer.analyzeLines(filePath, lines);
        archAnalyzer.analyzeLines(filePath, lines);
    }

    GitHistoryAnalyzer gitAnalyzer;
    gitAnalyzer.analyze(targetDir);

    ReportGenerator reportGen(scanner, cqAnalyzer, secAnalyzer, gitAnalyzer, archAnalyzer);
    std::string outFile = "intelligence_temp.json";
    reportGen.generateJsonReport(outFile);

    std::ifstream ifs(outFile);
    if (ifs.is_open()) {
        std::stringstream buffer;
        buffer << ifs.rdbuf();
        return buffer.str();
    }
    return "{}";
}

std::string LocalServer::getCorsHeaders() {
    return "HTTP/1.1 200 OK\r\n"
           "Access-Control-Allow-Origin: *\r\n"
           "Access-Control-Allow-Methods: GET, POST, OPTIONS\r\n"
           "Access-Control-Allow-Headers: Content-Type\r\n";
}

void LocalServer::start() {
#ifdef _WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port_);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    
    bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, SOMAXCONN);
    
    std::cout << "[Server] GitSense API listening on http://localhost:" << port_ << "\n";
    
    while (true) {
        SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket == INVALID_SOCKET) continue;
        
        char buffer[4096] = {0};
        recv(clientSocket, buffer, 4096, 0);
        std::string request(buffer);
        
        std::string response = "HTTP/1.1 404 Not Found\r\n\r\n";
        
        if (request.find("OPTIONS") == 0) {
            response = getCorsHeaders() + "Content-Length: 0\r\n\r\n";
        } 
        else if (request.find("GET /analyze?repo=") == 0) {
            size_t start = request.find("?repo=") + 6;
            size_t end = request.find(" ", start);
            std::string repoUrl = request.substr(start, end - start);
            
            // basic url decode %2F, %3A
            while(repoUrl.find("%2F") != std::string::npos) repoUrl.replace(repoUrl.find("%2F"), 3, "/");
            while(repoUrl.find("%3A") != std::string::npos) repoUrl.replace(repoUrl.find("%3A"), 3, ":");
            while(repoUrl.find("%20") != std::string::npos) repoUrl.replace(repoUrl.find("%20"), 3, " ");
            
            std::cout << "[Server] Analyzing: " << repoUrl << "\n";
            std::string jsonResult = runAnalysis(repoUrl);
            
            response = getCorsHeaders() + "Content-Type: application/json\r\n" +
                       "Content-Length: " + std::to_string(jsonResult.length()) + "\r\n\r\n" + jsonResult;
        }
        else if (request.find("POST /ask") == 0) {
            size_t bodyPos = request.find("\r\n\r\n");
            std::string body = "";
            if (bodyPos != std::string::npos) {
                body = request.substr(bodyPos + 4);
            }
            std::string repo = extractJsonStr(body, "repo");
            std::string question = extractJsonStr(body, "question");
            
            std::cout << "[Server] Question: " << question << "\n";
            
            // Read json
            std::ifstream ifs("intelligence_temp.json");
            std::stringstream sb;
            if (ifs.is_open()) sb << ifs.rdbuf();
            std::string context = sb.str();
            
            RepoAssistantEngine engine;
            std::string ans = engine.askQuestion(context, question);
            
            size_t pos = 0;
            while((pos = ans.find("\"", pos)) != std::string::npos) { ans.replace(pos, 1, "\\\""); pos += 2; }
            pos = 0;
            while((pos = ans.find("\n", pos)) != std::string::npos) { ans.replace(pos, 1, "\\n"); pos += 2; }
            
            std::string respJson = "{\"answer\": \"" + ans + "\"}";
            response = getCorsHeaders() + "Content-Type: application/json\r\n" +
                       "Content-Length: " + std::to_string(respJson.length()) + "\r\n\r\n" + respJson;
        }
        
        send(clientSocket, response.c_str(), response.length(), 0);
        closesocket(clientSocket);
    }
    
    closesocket(serverSocket);
    WSACleanup();
#endif
}
