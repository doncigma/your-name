cmake_minimum_required(VERSION 3.16)
project(YourName VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SDL2 packages
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Find or fetch nlohmann/json
find_package(nlohmann_json REQUIRED)

# Include directories
include_directories(inc)

# Source files
set(SOURCES
    src/main.cpp
)

# Header files
set(HEADERS
    inc/Entity.h
    inc/Game.h
    inc/GameEvent.h
    inc/InputManager.h
    inc/LevelManager.h
    inc/Player.h
    inc/Renderer.h
    inc/StateManager.h
    inc/Logger.h
    inc/AssetManager.h
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link libraries
target_link_libraries(${PROJECT_NAME} 
    SDL2::SDL2 
    SDL2::SDL2main
    SDL2_image::SDL2_image
    SDL2_mixer::SDL2_mixer
    SDL2_ttf::SDL2_ttf
    nlohmann_json::nlohmann_json
)

# Compiler options
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)

# Debug/Release configurations
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# Copy levels to build directory
add_custom_target(copy_levels ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets/levels
    ${CMAKE_BINARY_DIR}/assets/levels
    COMMENT "Copying levels to build directory"
)

# Make sure levels are copied before building executable
add_dependencies(${PROJECT_NAME} copy_levels)

# Copy other assets if they exist
if(EXISTS ${CMAKE_SOURCE_DIR}/assets)
    add_custom_target(copy_assets ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        ${CMAKE_BINARY_DIR}/assets
        COMMENT "Copying assets to build directory"
    )
    add_dependencies(${PROJECT_NAME} copy_assets)
endif()

# Print build info
message(STATUS "Building ${PROJECT_NAME} v${PROJECT_VERSION}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Assets will be copied to build directory")