#include <iostream>
#include <filesystem>
#include <fstream>
using namespace std;
namespace fs = std::filesystem;

int countLines(const fs::path& file) {
    ifstream in(file);
    int lines = 0;
    string s;
    while (getline(in, s)) lines++;
    return lines;
}

int main() {
    string path;
    cout << "Enter path of cloned repository: ";
    cin >> path;

    int fileCount = 0, lineCount = 0;

    for (auto &p : fs::recursive_directory_iterator(path)) {
        if (fs::is_regular_file(p)) {
            fileCount++;
            lineCount += countLines(p.path());
        }
    }

    cout << "\nRepository Analysis Report\n";
    cout << "Total files: " << fileCount << endl;
    cout << "Total lines of code: " << lineCount << endl;

    return 0;
}
