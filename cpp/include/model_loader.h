#pragma once

#include <string>
#include <vector>

namespace stable_audio {

/**
 * Model loader utilities for downloading and managing ONNX models.
 */
class ModelLoader {
public:
    /**
     * Download model from Hugging Face if not already cached.
     * @param model_id Hugging Face model identifier
     * @param cache_dir Cache directory
     * @param output_path Output path for ONNX model
     * @return true if successful
     */
    static bool DownloadAndConvert(
        const std::string& model_id,
        const std::string& cache_dir,
        const std::string& output_path
    );
    
    /**
     * Check if ONNX model exists at path.
     */
    static bool ModelExists(const std::string& model_path);
    
    /**
     * Get default cache directory.
     */
    static std::string GetCacheDir();
};

} // namespace stable_audio

