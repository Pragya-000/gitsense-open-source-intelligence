cmake_minimum_required(VERSION 3.10)
project(GitSense VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Internal includes
include_directories(include)

# Define source files
set(SOURCES
    src/main.cpp
    src/RepoFetcher.cpp
    src/FileScanner.cpp
    src/LanguageDetector.cpp
    src/StructureAnalyzer.cpp
    src/CodeQualityAnalyzer.cpp
    src/ArchitectureAnalyzer.cpp
    src/SecurityAnalyzer.cpp
    src/GitHistoryAnalyzer.cpp
    src/DocumentationAnalyzer.cpp
    src/LicenseAnalyzer.cpp
    src/DependencyAnalyzer.cpp
    src/ReportGenerator.cpp
)

# Create executable
add_executable(gitsense ${SOURCES})

# Target options
# target_link_libraries(gitsense pthread) 
