#include "audio_processor.h"
#include <fstream>
#include <algorithm>
#include <cmath>

namespace stable_audio {

// WAV file header structure
struct WAVHeader {
    char riff[4] = {'R', 'I', 'F', 'F'};
    uint32_t file_size;
    char wave[4] = {'W', 'A', 'V', 'E'};
    char fmt[4] = {'f', 'm', 't', ' '};
    uint32_t fmt_size = 16;
    uint16_t audio_format = 3; // IEEE float
    uint16_t num_channels;
    uint32_t sample_rate;
    uint32_t byte_rate;
    uint16_t block_align;
    uint16_t bits_per_sample = 32;
    char data[4] = {'d', 'a', 't', 'a'};
    uint32_t data_size;
};

bool AudioProcessor::SaveWAV(
    const std::vector<float>& samples,
    uint32_t sample_rate,
    uint32_t num_channels,
    const std::string& filepath
) {
    std::ofstream file(filepath, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }
    
    WAVHeader header;
    header.num_channels = static_cast<uint16_t>(num_channels);
    header.sample_rate = sample_rate;
    header.bits_per_sample = 32; // Float32
    header.byte_rate = sample_rate * num_channels * 4;
    header.block_align = static_cast<uint16_t>(num_channels * 4);
    
    uint32_t data_size = static_cast<uint32_t>(samples.size() * sizeof(float));
    header.data_size = data_size;
    header.file_size = 36 + data_size;
    
    // Write header
    file.write(reinterpret_cast<const char*>(&header), sizeof(WAVHeader));
    
    // Write samples
    file.write(reinterpret_cast<const char*>(samples.data()), data_size);
    
    file.close();
    return file.good();
}

bool AudioProcessor::LoadWAV(
    const std::string& filepath,
    std::vector<float>& samples,
    uint32_t& sample_rate,
    uint32_t& num_channels
) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }
    
    WAVHeader header;
    file.read(reinterpret_cast<char*>(&header), sizeof(WAVHeader));
    
    if (std::string(header.riff, 4) != "RIFF" || 
        std::string(header.wave, 4) != "WAVE") {
        return false;
    }
    
    sample_rate = header.sample_rate;
    num_channels = header.num_channels;
    
    // Read samples (assuming float32)
    size_t num_samples = header.data_size / sizeof(float);
    samples.resize(num_samples);
    file.read(reinterpret_cast<char*>(samples.data()), header.data_size);
    
    file.close();
    return file.good();
}

bool AudioProcessor::Resample(
    const std::vector<float>& input_samples,
    uint32_t input_sample_rate,
    std::vector<float>& output_samples,
    uint32_t output_sample_rate
) {
    if (input_sample_rate == output_sample_rate) {
        output_samples = input_samples;
        return true;
    }
    
    // Simple linear interpolation resampling
    // For production, use libsamplerate or similar
    double ratio = static_cast<double>(output_sample_rate) / input_sample_rate;
    size_t output_size = static_cast<size_t>(input_samples.size() * ratio);
    output_samples.resize(output_size);
    
    for (size_t i = 0; i < output_size; ++i) {
        double pos = i / ratio;
        size_t idx = static_cast<size_t>(pos);
        double frac = pos - idx;
        
        if (idx + 1 < input_samples.size()) {
            output_samples[i] = static_cast<float>(
                input_samples[idx] * (1.0 - frac) + 
                input_samples[idx + 1] * frac
            );
        } else {
            output_samples[i] = input_samples[idx];
        }
    }
    
    return true;
}

void AudioProcessor::MonoToStereo(
    const std::vector<float>& mono,
    std::vector<float>& stereo
) {
    stereo.resize(mono.size() * 2);
    for (size_t i = 0; i < mono.size(); ++i) {
        stereo[i * 2] = mono[i];
        stereo[i * 2 + 1] = mono[i];
    }
}

void AudioProcessor::Normalize(std::vector<float>& samples) {
    if (samples.empty()) return;
    
    float max_val = 0.0f;
    for (float sample : samples) {
        float abs_val = std::abs(sample);
        if (abs_val > max_val) {
            max_val = abs_val;
        }
    }
    
    if (max_val > 0.0f && max_val <= 1.0f) {
        // Already normalized
        return;
    }
    
    if (max_val > 0.0f) {
        float scale = 1.0f / max_val;
        for (float& sample : samples) {
            sample *= scale;
        }
    }
}

} // namespace stable_audio

