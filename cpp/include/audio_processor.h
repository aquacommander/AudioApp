#pragma once

#include <vector>
#include <string>
#include <cstdint>

namespace stable_audio {

/**
 * Audio processing utilities for WAV file I/O and audio manipulation.
 */
class AudioProcessor {
public:
    /**
     * Save audio samples to WAV file.
     * @param samples Audio samples (mono or stereo interleaved)
     * @param sample_rate Sample rate in Hz
     * @param num_channels Number of channels (1 = mono, 2 = stereo)
     * @param filepath Output file path
     * @return true if successful
     */
    static bool SaveWAV(
        const std::vector<float>& samples,
        uint32_t sample_rate,
        uint32_t num_channels,
        const std::string& filepath
    );
    
    /**
     * Load audio from WAV file.
     * @param filepath Input file path
     * @param samples Output audio samples
     * @param sample_rate Output sample rate
     * @param num_channels Output number of channels
     * @return true if successful
     */
    static bool LoadWAV(
        const std::string& filepath,
        std::vector<float>& samples,
        uint32_t& sample_rate,
        uint32_t& num_channels
    );
    
    /**
     * Resample audio to target sample rate.
     * @param input_samples Input samples
     * @param input_sample_rate Input sample rate
     * @param output_samples Output samples
     * @param output_sample_rate Target sample rate
     * @return true if successful
     */
    static bool Resample(
        const std::vector<float>& input_samples,
        uint32_t input_sample_rate,
        std::vector<float>& output_samples,
        uint32_t output_sample_rate
    );
    
    /**
     * Convert mono to stereo.
     */
    static void MonoToStereo(
        const std::vector<float>& mono,
        std::vector<float>& stereo
    );
    
    /**
     * Normalize audio samples to [-1, 1] range.
     */
    static void Normalize(std::vector<float>& samples);
};

} // namespace stable_audio

