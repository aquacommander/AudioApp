#pragma once

#include <string>
#include <vector>

namespace stable_audio {

/**
 * Utility functions for string processing, file operations, etc.
 */
class Utils {
public:
    /**
     * Split string by delimiter.
     */
    static std::vector<std::string> SplitString(
        const std::string& str,
        const std::string& delimiter
    );
    
    /**
     * Trim whitespace from string.
     */
    static std::string Trim(const std::string& str);
    
    /**
     * Check if file exists.
     */
    static bool FileExists(const std::string& filepath);
    
    /**
     * Get file extension.
     */
    static std::string GetFileExtension(const std::string& filepath);
    
    /**
     * Join path components.
     */
    static std::string JoinPath(
        const std::string& base,
        const std::string& path
    );
};

} // namespace stable_audio

