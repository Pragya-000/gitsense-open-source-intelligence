# GitSense – Open Source Intelligence Platform

<<<<<<< HEAD
**"GitSense: X-Ray Vision for Open Source Ecosystems"**

GitSense is a high-performance, fully offline, AI-powered system that analyzes open-source repositories to evaluate code quality, security patterns, architecture smells, and dependency risks. Developed as part of **FOSS Hack 2026**.

## 🚀 Features
- Recursively scan local or remote repositories instantly.
- Collect metrics: Total files, Lines of Code (LoC), Comment/Blank line percentages.
- **Code Quality Analyzer**: Detects `TODO` comments, overly long functions, and deep nesting.
- **Security Analyzer**: Identifies dangerous memory C/C++ variants (e.g. `strcpy`), usage of `system()`, and hardcoded secrets (e.g. `API_KEY`).
- Output data into an interactive terminal interface or generate structured `intelligence.json` artifacts for CI automation.

## 🛠 Tech Stack
- **C++17** (Ultra-high performance static scanning core)
- **MinGW / GCC**
- **CMake**
- Native POSIX file iterators (`dirent.h`)

## 🏗️ Building and Running

You can compile the system locally using MinGW (`g++`):

```powershell
cd gitsense
g++ -std=c++17 -Iinclude src/*.cpp -o gitsense.exe

# Scan a local repository mapping natively through the terminal
.\gitsense.exe scan .

# Output a comprehensive JSON artifact
.\gitsense.exe scan . report --json
```

## 🎯 Goal
To build an intelligence layer over open-source repositories that helps contributors and companies vet project quality and risks entirely offline.

## 📈 Future Scope
- Architecture Detector (God objects, tight-coupling graphs).
- Machine learning/Local LLM integration for auto-remediation patches.
- Semantic code similarity search powered by local vector embeddings.
- Full Git History analysis (Bus Factor calculation, maintainer heatmaps).
=======
GitSense is an intelligent system that analyzes open-source repositories to evaluate code quality, security, and community health.

## 🚀 Features
- Analyze a GitHub repository using its URL
- Count number of files and lines of code
- Detect programming languages used
- Evaluate README and documentation quality
- Generate a basic project health score

## 🛠 Tech Stack
- C++
- Git
- File system analysis

## 🎯 Goal
To build an intelligence layer over open-source repositories that helps contributors and maintainers understand project quality and risks.

## 📈 Future Scope
- Security vulnerability detection
- Dependency analysis
- Machine learning based project health prediction
- Web dashboard

---

Developed as part of FOSS Hack 2026.
>>>>>>> 21440a24069c7ea8aa3c5ec7ee9266bb2ede47ee
Minor Update