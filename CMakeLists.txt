cmake_minimum_required(VERSION 3.20)
project(Campfire-Engine LANGUAGES CXX C)

# Global compiler config
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# This will be compiled as a library stored in /lib
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

#### External dependencies configuration. ####
include(FetchContent)

#SDL2
FetchContent_Declare(
        SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.32.0)

# SDL_image
FetchContent_Declare(
        SDL_image
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
        GIT_TAG release-2.8.3)

# SDL_ttf
FetchContent_Declare(
        SDL_ttf
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
        GIT_TAG release-2.24.0)

# SDL_mixer
FetchContent_Declare(
        SDL_mixer
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
        GIT_TAG release-2.8.0)

# Build optimizations
set(SDL_SHARED ON CACHE BOOL "" FORCE)
set(SDL_STATIC OFF CACHE BOOL "" FORCE)
set(SDL_TEST OFF CACHE BOOL "" FORCE)

# Ensure driver compatibility
set(SDL_PIPEWIRE OFF CACHE BOOL "" FORCE)

# Download and make external libs available
FetchContent_MakeAvailable(SDL2 SDL_image SDL_ttf SDL_mixer)

#### Project dependencies configuration ####

# Configure file sources
file(GLOB_RECURSE ENGINE_HEADERS CONFIGURE_DEPENDS "include/*.h")
file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS "src/*.cpp")

# The GLAD library will be compiled together the source codes
set(GLAD_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/external/glad/glad.c")

# Configure this as a library
add_library(${PROJECT_NAME} STATIC ${ENGINE_SOURCES} ${ENGINE_HEADERS} ${GLAD_SOURCE})

# Configure the engine headers as the public API
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# External header only libraries only accessible by this project
target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/external
        ${CMAKE_CURRENT_SOURCE_DIR}/external/glad
)

# The engine uses this libraries internally
target_link_libraries(${PROJECT_NAME} PRIVATE
        SDL2::SDL2
        SDL2_image::SDL2_image
        SDL2_ttf::SDL2_ttf
        SDL2_mixer::SDL2_mixer
        ${CMAKE_DL_LIBS}
)

message(STATUS "Campfire Engine successfully configure to compile")