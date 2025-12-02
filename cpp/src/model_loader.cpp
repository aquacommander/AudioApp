#include "model_loader.h"
#include "utils.h"
#include <fstream>
#include <cstdlib>

namespace stable_audio {

bool ModelLoader::DownloadAndConvert(
    const std::string& model_id,
    const std::string& cache_dir,
    const std::string& output_path
) {
    // This would call the Python conversion script
    // For now, just check if model exists
    if (Utils::FileExists(output_path)) {
        return true;
    }
    
    // TODO: Implement actual download and conversion
    // This would spawn the Python conversion script
    
    return false;
}

bool ModelLoader::ModelExists(const std::string& model_path) {
    return Utils::FileExists(model_path);
}

std::string ModelLoader::GetCacheDir() {
    #ifdef _WIN32
        const char* home = std::getenv("USERPROFILE");
        if (home) {
            return Utils::JoinPath(home, ".cache/stable_audio");
        }
    #else
        const char* home = std::getenv("HOME");
        if (home) {
            return Utils::JoinPath(home, ".cache/stable_audio");
        }
    #endif
    
    return ".cache/stable_audio";
}

} // namespace stable_audio

