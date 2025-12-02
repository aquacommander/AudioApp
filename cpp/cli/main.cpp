#include "../include/inference_engine.h"
#include "../include/audio_processor.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstring>

void PrintUsage(const char* program_name) {
    std::cout << "Usage: " << program_name << " [OPTIONS]\n"
              << "Generate audio from text prompt using Stable Audio ONNX model.\n\n"
              << "Options:\n"
              << "  --model PATH          Path to ONNX model file (required)\n"
              << "  --prompt TEXT         Text prompt describing audio (required)\n"
              << "  --output PATH         Output WAV file path (default: output.wav)\n"
              << "  --seconds FLOAT       Duration in seconds (default: 11.0)\n"
              << "  --bars INT            Number of musical bars (overrides seconds)\n"
              << "  --bpm INT             Beats per minute (default: 120)\n"
              << "  --seed INT            Random seed (0 = random, default: 0)\n"
              << "  --device DEVICE       Device: cpu, cuda, coreml (default: cpu)\n"
              << "  --help                Show this help message\n"
              << std::endl;
}

int CalculateSecondsFromBars(int bars, int bpm, int beats_per_bar = 4) {
    int beats_total = bars * beats_per_bar;
    return static_cast<int>((beats_total * 60.0) / bpm);
}

int main(int argc, char* argv[]) {
    std::string model_path;
    std::string prompt;
    std::string output_path = "output.wav";
    float seconds = 11.0f;
    int bars = 0;
    int bpm = 120;
    uint32_t seed = 0;
    std::string device = "cpu";
    
    // Parse arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            PrintUsage(argv[0]);
            return 0;
        } else if (strcmp(argv[i], "--model") == 0 && i + 1 < argc) {
            model_path = argv[++i];
        } else if (strcmp(argv[i], "--prompt") == 0 && i + 1 < argc) {
            prompt = argv[++i];
        } else if (strcmp(argv[i], "--output") == 0 && i + 1 < argc) {
            output_path = argv[++i];
        } else if (strcmp(argv[i], "--seconds") == 0 && i + 1 < argc) {
            seconds = std::stof(argv[++i]);
        } else if (strcmp(argv[i], "--bars") == 0 && i + 1 < argc) {
            bars = std::stoi(argv[++i]);
        } else if (strcmp(argv[i], "--bpm") == 0 && i + 1 < argc) {
            bpm = std::stoi(argv[++i]);
        } else if (strcmp(argv[i], "--seed") == 0 && i + 1 < argc) {
            seed = static_cast<uint32_t>(std::stoul(argv[++i]));
        } else if (strcmp(argv[i], "--device") == 0 && i + 1 < argc) {
            device = argv[++i];
        } else {
            std::cerr << "Unknown option: " << argv[i] << std::endl;
            PrintUsage(argv[0]);
            return 1;
        }
    }
    
    // Validate required arguments
    if (model_path.empty()) {
        std::cerr << "Error: --model is required" << std::endl;
        PrintUsage(argv[0]);
        return 1;
    }
    
    if (prompt.empty()) {
        std::cerr << "Error: --prompt is required" << std::endl;
        PrintUsage(argv[0]);
        return 1;
    }
    
    // Calculate seconds from bars if specified
    if (bars > 0) {
        seconds = static_cast<float>(CalculateSecondsFromBars(bars, bpm));
        std::cout << "Calculated " << seconds << " seconds for " << bars 
                  << " bars at " << bpm << " BPM" << std::endl;
    }
    
    // Build enhanced prompt
    std::string enhanced_prompt = prompt;
    if (bars > 0) {
        enhanced_prompt = std::to_string(bars) + " bar loop, " + enhanced_prompt;
    }
    if (bpm > 0) {
        enhanced_prompt = std::to_string(bpm) + " BPM, " + enhanced_prompt;
    }
    
    std::cout << "Stable Audio Generator (C++/ONNX)" << std::endl;
    std::cout << "=================================" << std::endl;
    std::cout << "Model: " << model_path << std::endl;
    std::cout << "Prompt: " << enhanced_prompt << std::endl;
    std::cout << "Duration: " << seconds << " seconds" << std::endl;
    std::cout << "Device: " << device << std::endl;
    if (seed > 0) {
        std::cout << "Seed: " << seed << std::endl;
    }
    std::cout << std::endl;
    
    // Initialize inference engine
    stable_audio::InferenceEngine engine;
    
    std::cout << "Loading model..." << std::endl;
    if (!engine.LoadModel(model_path, device)) {
        std::cerr << "Failed to load model: " << model_path << std::endl;
        return 1;
    }
    
    std::cout << engine.GetModelInfo() << std::endl;
    std::cout << std::endl;
    
    // Generate audio
    std::cout << "Generating audio..." << std::endl;
    std::vector<float> samples;
    uint32_t sample_rate;
    
    if (!engine.Generate(enhanced_prompt, seconds, seed, samples, sample_rate)) {
        std::cerr << "Failed to generate audio" << std::endl;
        return 1;
    }
    
    // Save to WAV file
    std::cout << "Saving audio to: " << output_path << std::endl;
    if (!stable_audio::AudioProcessor::SaveWAV(samples, sample_rate, 2, output_path)) {
        std::cerr << "Failed to save WAV file" << std::endl;
        return 1;
    }
    
    std::cout << std::endl;
    std::cout << "✅ Success!" << std::endl;
    std::cout << "   Duration: " << (samples.size() / sample_rate) << " seconds" << std::endl;
    std::cout << "   Sample rate: " << sample_rate << " Hz" << std::endl;
    std::cout << "   Output file: " << output_path << std::endl;
    
    return 0;
}

