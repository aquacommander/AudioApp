#include "utils.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

namespace stable_audio {

std::vector<std::string> Utils::SplitString(
    const std::string& str,
    const std::string& delimiter
) {
    std::vector<std::string> result;
    size_t start = 0;
    size_t end = str.find(delimiter);
    
    while (end != std::string::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }
    
    result.push_back(str.substr(start));
    return result;
}

std::string Utils::Trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) {
        return "";
    }
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, last - first + 1);
}

bool Utils::FileExists(const std::string& filepath) {
    std::ifstream file(filepath);
    return file.good();
}

std::string Utils::GetFileExtension(const std::string& filepath) {
    size_t dot_pos = filepath.find_last_of('.');
    if (dot_pos != std::string::npos) {
        return filepath.substr(dot_pos + 1);
    }
    return "";
}

std::string Utils::JoinPath(
    const std::string& base,
    const std::string& path
) {
    if (base.empty()) return path;
    if (path.empty()) return base;
    
    char last_char = base.back();
    if (last_char == '/' || last_char == '\\') {
        return base + path;
    }
    
    #ifdef _WIN32
        return base + "\\" + path;
    #else
        return base + "/" + path;
    #endif
}

} // namespace stable_audio

