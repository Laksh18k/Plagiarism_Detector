#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

string FileManager::read(const string& filepath) {
    ifstream file(filepath);
    if (!file.is_open()) {
        throw runtime_error("File not found: " + filepath);
    }
    ostringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}