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
file(GLOB_RECURSE ENGINE_HEADERS CONFIGURE_DEPENDS
        "Include/Core/*.h"
        "Include/Graphics/*.h"
        "Include/Graphics/Renderer/*.h"
        "Include/Math/*.h"
        "Include/Types/*.h"
        "Include/Utils/*.h"
)
file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS
        "Src/Core/*.cpp"
        "Src/Graphics/*.cpp"
        "Src/Graphics/Renderer/*.cppp"
        "Src/Math/*.cpp"
        "Src/Utils/*.cpp"
)

# The GLAD library will be compiled together the source codes
set(GLAD_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/External/glad/glad.c"
        Include/Graphics/Shader/Shader.h
        Src/Graphics/Shader/Shader.cpp
        Include/Graphics/Shader/UniformsBlock.h
        Src/Graphics/Shader/UniformsBlock.cpp
        Include/Graphics/Shader/ShadersManager.h
        Src/Graphics/Shader/ShadersManager.cpp
        Include/Utils/FileUtils.h
        Src/Utils/FileUtils.cpp
        Include/Graphics/PostEffect/FrameBuffer.h
        Include/Graphics/Geometry/VertexArray.h
        Src/Graphics/Geometry/VertexArray.cpp
        Src/Graphics/PostEffect/FrameBuffer.cpp
        Include/Graphics/Resources/Texture.h
        Src/Graphics/Resources/Texture.cpp
        Include/Graphics/PostEffect/PostEffect.h
        Src/Graphics/PostEffect/PostEffect.cpp
        Include/Graphics/PostEffect/PostEffectsManager.h
        Src/Graphics/PostEffect/PostEffectsManager.cpp
        Include/Graphics/Renderer/Drawer.h
        Src/Graphics/Renderer/Drawer.cpp
        Include/Factories/ObjectFactories.h
        Src/Factories/ObjectFactories.cpp
)

# Configure this as a library
add_library(${PROJECT_NAME} STATIC ${ENGINE_SOURCES} ${ENGINE_HEADERS} ${GLAD_SOURCE})

# Configure headers location internally and externally
target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Include
        ${CMAKE_CURRENT_SOURCE_DIR}/External
        ${CMAKE_CURRENT_SOURCE_DIR}/External/glad

        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
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