cmake_minimum_required(VERSION 3.18)
project(StableAudioGenerator VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build options
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(BUILD_TESTS "Build tests" ON)
option(BUILD_CLI "Build command-line tool" ON)
option(BUILD_SERVER "Build REST API server" ON)

# Platform-specific settings
if(WIN32)
    add_definitions(-D_WIN32_WINNT=0x0A00)  # Windows 10
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
elseif(APPLE)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15")
    set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64")
elseif(UNIX AND NOT APPLE)
    # Linux/Ubuntu
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Find ONNX Runtime
find_package(onnxruntime QUIET)
if(NOT onnxruntime_FOUND)
    message(STATUS "ONNX Runtime not found via CMake, using manual setup")
    # Manual ONNX Runtime setup will be handled in src/CMakeLists.txt
endif()

# Find required packages
find_package(Threads REQUIRED)

# Audio libraries
find_package(libsamplerate QUIET)  # For audio resampling
find_package(OpenMP QUIET)  # Optional for performance

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Add subdirectories
add_subdirectory(src)

if(BUILD_CLI)
    add_subdirectory(cli)
endif()

if(BUILD_SERVER)
    add_subdirectory(server)
endif()

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Installation
install(TARGETS stable_audio_core
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY include/ DESTINATION include
    FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
)

