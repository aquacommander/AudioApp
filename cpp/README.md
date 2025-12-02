# C++ Core Library

This directory contains the C++ core implementation using ONNX Runtime for cross-platform audio generation.

## Structure

```
cpp/
├── CMakeLists.txt          # Main CMake configuration
├── include/                # Public headers
│   ├── inference_engine.h  # Main inference interface
│   ├── audio_processor.h   # Audio I/O utilities
│   ├── model_loader.h      # Model loading utilities
│   └── utils.h             # Utility functions
├── src/                    # Implementation files
│   ├── inference_engine.cpp
│   ├── audio_processor.cpp
│   ├── model_loader.cpp
│   └── utils.cpp
├── cli/                    # Command-line tool
│   ├── CMakeLists.txt
│   └── main.cpp
├── server/                 # REST API server (optional)
│   ├── CMakeLists.txt
│   └── main.cpp
└── tests/                  # Test suite
    ├── CMakeLists.txt
    └── test_*.cpp
```

## Building

See [BUILD.md](../BUILD.md) for detailed build instructions.

Quick start:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Usage

### Command-Line Tool

```bash
./build/bin/stable_audio_cli \
    --model models/stable_audio.onnx \
    --prompt "120 BPM, 4 bar loop, electric piano" \
    --output output.wav \
    --seconds 11 \
    --seed 42
```

### C++ API

```cpp
#include "inference_engine.h"
#include "audio_processor.h"

// Initialize engine
stable_audio::InferenceEngine engine;
engine.LoadModel("models/stable_audio.onnx", "cpu");

// Generate audio
std::vector<float> samples;
uint32_t sample_rate;
engine.Generate(
    "120 BPM, 4 bar loop, electric piano",
    11.0f,  // seconds
    42,     // seed
    samples,
    sample_rate
);

// Save to WAV
stable_audio::AudioProcessor::SaveWAV(
    samples, sample_rate, 2, "output.wav"
);
```

## Dependencies

- ONNX Runtime (platform-specific)
- C++17 compiler
- CMake 3.18+

## Platform Support

- ✅ Windows (x64)
- ✅ macOS (x86_64, arm64)
- ✅ Linux/Ubuntu (x64)
- 🔄 Android (in progress)
- 🔄 iOS (in progress)

## Notes

- The ONNX model must be converted first using `scripts/convert_to_onnx.py`
- ONNX Runtime must be downloaded and placed in `third_party/`
- See [BUILD.md](../BUILD.md) for platform-specific setup

