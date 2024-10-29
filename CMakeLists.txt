cmake_minimum_required(VERSION 3.16)  # CMake version check
project(kica_aes)                     # Create project "simple_example"
set(CMAKE_CXX_STANDARD 20)            # Enable c++20 standard
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Enable compile commands for clang-tidy

# Add main.cpp file of the project root directory as a source file
set(SOURCE_FILES src/main.cpp)

# Add include files
include_directories(include)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(kica_aes ${SOURCE_FILES})