cmake_minimum_required(VERSION 3.10)

# Name of the project
project(chip8-emulator)

# Find source and header files
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.h")

# Warn if no source/header files are found
if(NOT SOURCES)
    message(WARNING "No source files found in src/")
endif()

if(NOT HEADERS)
    message(WARNING "No header files found in src/")
endif()

# Set the executable
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES} ${HEADERS})

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD_REQUIRED YES)
SET_TARGET_PROPERTIES(${CMAKE_PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
SET_TARGET_PROPERTIES(${CMAKE_PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

# Set the output directory for the built executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
