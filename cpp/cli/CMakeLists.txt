# Command-line tool
add_executable(stable_audio_cli main.cpp)

target_link_libraries(stable_audio_cli PRIVATE stable_audio_core)

# Install
install(TARGETS stable_audio_cli DESTINATION bin)

