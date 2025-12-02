# Example Audio Outputs

This directory contains sample audio files generated using the Stable Audio Generator.

## Sample Files

Examples will be generated using the C++ command-line tool:

```bash
./build/bin/stable_audio_cli \
    --model models/stable_audio.onnx \
    --prompt "120 BPM, 4 bar loop, electric piano, C major" \
    --bars 4 \
    --bpm 120 \
    --key C \
    --seed 42 \
    --output examples/example_1_electric_piano.wav
```

## Generating Examples

### Example 1: Electric Piano Loop
```bash
./build/bin/stable_audio_cli \
    --model models/stable_audio.onnx \
    --prompt "120 BPM, 4 bar loop, electric piano, C major" \
    --bars 4 \
    --bpm 120 \
    --key C \
    --seed 42 \
    --output examples/example_1_electric_piano.wav
```

### Example 2: Synth Arpeggio
```bash
./build/bin/stable_audio_cli \
    --model models/stable_audio.onnx \
    --prompt "120 BPM, 4 bars, synth arpeggio, D minor" \
    --bars 4 \
    --bpm 120 \
    --key D \
    --seed 123 \
    --output examples/example_2_synth_arpeggio.wav
```

### Example 3: Drum Loop
```bash
./build/bin/stable_audio_cli \
    --model models/stable_audio.onnx \
    --prompt "128 BPM, 8 bar loop, electronic drum beat, punchy kick and snare" \
    --bars 8 \
    --bpm 128 \
    --seed 456 \
    --output examples/example_3_drum_loop.wav
```

## Notes

- These examples demonstrate the model's ability to generate musical loops
- Each file should be generated using the command-line tool
- Files are suitable for testing loop playback and gapless transitions
- Actual audio files will be generated during Milestone 1 delivery

## Expected File Sizes

- 8-second WAV (44.1kHz, stereo): ~1.4 MB
- 15-second WAV (44.1kHz, stereo): ~2.6 MB
