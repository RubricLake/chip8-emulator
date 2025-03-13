cmake_minimum_required(VERSION 3.30)

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
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

SET_TARGET_PROPERTIES(${CMAKE_PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

# Set the output directory for the built executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(CHIP8_VENDORED "Use vendored libraries" OFF)

if(CHIP8_VENDORED)
    # This assumes you have added SDL as a submodule in vendored/SDL
    add_subdirectory(SDL-release-3.2.8 EXCLUDE_FROM_ALL)
else()
    # 1. Look for a SDL3 package,
    # 2. look for the SDL3-shared component, and
    # 3. fail if the shared component cannot be found.
    find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
endif()

# Link to the actual SDL3 library.
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)

if(WIN32)
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:SDL3::SDL3-shared> $<TARGET_FILE_DIR:${PROJECT_NAME}>
        VERBATIM
    )
endif()