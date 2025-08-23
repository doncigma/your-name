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

# Include directories
include_directories(inc)

# Source files
set(SOURCES
    src/main.cpp
    src/Game.cpp
    src/Entity.cpp
    src/Player.cpp
    src/Renderer.cpp
    src/InputManager.cpp
    src/MenuState.cpp
    src/PlayState.cpp
    src/PauseState.cpp
)

# Header files
set(HEADERS
    inc/Game.h
    inc/GameState.h
    inc/Entity.h
    inc/Player.h
    inc/Renderer.h
    inc/InputManager.h
    inc/MenuState.h
    inc/PlayState.h
    inc/PauseState.h
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link SDL2 libraries
target_link_libraries(${PROJECT_NAME} 
    SDL2::SDL2 
    SDL2::SDL2main
    SDL2_image::SDL2_image
    SDL2_mixer::SDL2_mixer
    SDL2_ttf::SDL2_ttf
)

# Compiler options
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)

# Debug/Release configurations
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# Copy assets to build directory (if you create an assets folder)
# if(EXISTS ${CMAKE_SOURCE_DIR}/assets)
#     file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
# endif()

# Print build info
message(STATUS "Building ${PROJECT_NAME} v${PROJECT_VERSION}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")