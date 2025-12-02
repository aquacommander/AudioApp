# Mobile Proof-of-Concept - Milestone 1

This directory contains proof-of-concept implementations for mobile platforms (Android and iOS).

## Overview

For Milestone 1, mobile proof-of-concept demonstrates:
- Model can be loaded on mobile devices
- Basic inference can be performed
- Generated output can be saved to device storage

Full mobile optimization and packaging will be completed in Milestone 2.

## Android

### Requirements

- Android Studio (latest version)
- Android SDK (API 21+)
- Android NDK (for native libraries)
- Java/Kotlin development environment

### Approach

Two approaches are being explored:

1. **ONNX Runtime Mobile**: Convert model to ONNX format and use ONNX Runtime Mobile
2. **PyTorch Mobile**: Use PyTorch Mobile for Android

### Proof-of-Concept Steps

1. **Model Conversion**
   ```bash
   # Convert to ONNX (if supported)
   python mobile/android/convert_to_onnx.py
   
   # Or convert to PyTorch Mobile
   python mobile/android/convert_to_mobile.py
   ```

2. **Android Project Setup**
   - See `mobile/android/README.md` for detailed instructions
   - Build APK with embedded model
   - Test inference on device

3. **Expected Output**
   - Logs showing model loaded successfully
   - Generated audio file saved to device storage
   - Sample inference timing logs

### Current Status

- [ ] Model conversion scripts created
- [ ] Android project structure setup
- [ ] Basic inference test implemented
- [ ] Build logs/screenshots available

## iOS

### Requirements

- Xcode (latest version)
- iOS SDK (14.0+)
- Swift development environment

### Approach

Two approaches are being explored:

1. **CoreML**: Convert model to CoreML format for native iOS performance
2. **PyTorch Mobile**: Use PyTorch Mobile for iOS

### Proof-of-Concept Steps

1. **Model Conversion**
   ```bash
   # Convert to CoreML (if supported)
   python mobile/ios/convert_to_coreml.py
   
   # Or use PyTorch Mobile
   python mobile/ios/convert_to_mobile.py
   ```

2. **iOS Project Setup**
   - See `mobile/ios/README.md` for detailed instructions
   - Build iOS app with embedded model
   - Test on device or simulator

3. **Expected Output**
   - Logs showing model loaded successfully
   - Generated audio file saved to app documents
   - Sample inference timing logs

### Current Status

- [ ] Model conversion scripts created
- [ ] iOS project structure setup
- [ ] Basic inference test implemented
- [ ] Build logs/screenshots available

## Notes

- Full mobile optimization (quantization, pruning) will be done in Milestone 2
- Real-time generation constraints will be addressed in later milestones
- Mobile builds may require model size optimization for app store limits

## Deliverables for Milestone 1

For Milestone 1, proof-of-concept includes:

1. Documentation of mobile approach
2. Conversion scripts (even if not fully working)
3. Build logs or screenshots showing:
   - Model file loaded on device
   - Inference attempted (even if slow)
   - Output file created

Full working mobile apps will be delivered in Milestone 2.

