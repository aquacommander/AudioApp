# Core library sources
set(CORE_SOURCES
    inference_engine.cpp
    audio_processor.cpp
    model_loader.cpp
    utils.cpp
)

set(CORE_HEADERS
    ../include/inference_engine.h
    ../include/audio_processor.h
    ../include/model_loader.h
    ../include/utils.h
)

# ONNX Runtime paths (will be configured based on platform)
if(WIN32)
    set(ONNX_RUNTIME_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../third_party/onnxruntime-win")
elseif(APPLE)
    set(ONNX_RUNTIME_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../third_party/onnxruntime-osx")
elseif(UNIX)
    set(ONNX_RUNTIME_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../third_party/onnxruntime-linux")
endif()

# Find ONNX Runtime manually if not found
if(NOT onnxruntime_FOUND)
    message(STATUS "Setting up ONNX Runtime from: ${ONNX_RUNTIME_DIR}")
    
    if(EXISTS "${ONNX_RUNTIME_DIR}/include")
        include_directories(${ONNX_RUNTIME_DIR}/include)
    endif()
    
    if(EXISTS "${ONNX_RUNTIME_DIR}/lib")
        link_directories(${ONNX_RUNTIME_DIR}/lib)
    endif()
endif()

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${ONNX_RUNTIME_DIR}/include
)

# Link libraries
set(LINK_LIBS
    Threads::Threads
)

# Add ONNX Runtime library
if(onnxruntime_FOUND)
    list(APPEND LINK_LIBS onnxruntime::onnxruntime)
else()
    if(WIN32)
        list(APPEND LINK_LIBS onnxruntime)
    else()
        list(APPEND LINK_LIBS onnxruntime)
    endif()
endif()

# Optional audio processing
if(libsamplerate_FOUND)
    list(APPEND LINK_LIBS samplerate)
    add_definitions(-DHAVE_LIBSAMPLERATE)
endif()

# Create library
add_library(stable_audio_core STATIC ${CORE_SOURCES} ${CORE_HEADERS})

target_link_libraries(stable_audio_core PRIVATE ${LINK_LIBS})

# Platform-specific settings
if(WIN32)
    target_compile_definitions(stable_audio_core PRIVATE _WIN32)
elseif(APPLE)
    target_compile_definitions(stable_audio_core PRIVATE __APPLE__)
    # Link against CoreAudio framework
    find_library(COREAUDIO_LIBRARY CoreAudio)
    if(COREAUDIO_LIBRARY)
        target_link_libraries(stable_audio_core PRIVATE ${COREAUDIO_LIBRARY})
    endif()
elseif(UNIX)
    target_compile_definitions(stable_audio_core PRIVATE __LINUX__)
    # Link against ALSA or PulseAudio
    find_library(ASOUND_LIBRARY asound)
    if(ASOUND_LIBRARY)
        target_link_libraries(stable_audio_core PRIVATE ${ASOUND_LIBRARY})
    endif()
endif()

# Compiler flags
target_compile_options(stable_audio_core PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /EHsc>
    $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Wpedantic>
    $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra -Wpedantic>
)

# Export symbols
set_target_properties(stable_audio_core PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)

