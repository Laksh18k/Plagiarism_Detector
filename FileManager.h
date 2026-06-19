#pragma once

#include <string>
#include <stdexcept>

using namespace std;

class FileManager {
public:
    static string read(const string& filepath);
};