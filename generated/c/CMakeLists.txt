# Generated CMake project. Do not edit by hand.
cmake_minimum_required(VERSION 3.10)

project(open_earable_protocols LANGUAGES C)

add_library(open_earable_protocols STATIC
    "src/protocol_runtime.c"
    "src/audio_response_protocol.c"
)
add_library(OpenEarable::Protocols ALIAS open_earable_protocols)

target_compile_features(open_earable_protocols PUBLIC c_std_99)
target_include_directories(open_earable_protocols
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
)
