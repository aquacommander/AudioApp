#pragma once

#include <string>
#include <vector>
#include <memory>
#include <cstdint>

namespace stable_audio {

/**
 * Inference engine for Stable Audio generation using ONNX Runtime.
 */
class InferenceEngine {
public:
    InferenceEngine();
    ~InferenceEngine();

    /**
     * Load ONNX model from file.
     * @param model_path Path to ONNX model file
     * @param device Device to run on ("cpu", "cuda", "coreml", etc.)
     * @return true if successful
     */
    bool LoadModel(const std::string& model_path, const std::string& device = "cpu");

    /**
     * Generate audio from text prompt.
     * @param prompt Text prompt describing desired audio
     * @param duration_seconds Duration in seconds
     * @param seed Random seed for deterministic output (0 = random)
     * @param output_samples Output vector for generated audio samples
     * @param sample_rate Output sample rate
     * @return true if successful
     */
    bool Generate(
        const std::string& prompt,
        float duration_seconds,
        uint32_t seed,
        std::vector<float>& output_samples,
        uint32_t& sample_rate
    );

    /**
     * Check if model is loaded.
     */
    bool IsModelLoaded() const;

    /**
     * Get model information.
     */
    std::string GetModelInfo() const;

    /**
     * Set generation parameters.
     */
    void SetNumInferenceSteps(int steps);
    void SetGuidanceScale(float scale);

private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
};

} // namespace stable_audio

