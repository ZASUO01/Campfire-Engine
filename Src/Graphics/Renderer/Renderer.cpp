#include "Graphics/Renderer/Renderer.h"
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include "Utils/SDLUtils.h"

Renderer::Renderer(SDL_Window *window, const int width, const int height)
:mScreenWidth(width)
,mScreenHeight(height)
,mWindow(window)
{}

Renderer::~Renderer() = default;

void SDL_GLContextDeleter::operator()(void* context) const {
    SDLUtils::SDL_GLContextDeleter()(context);
}

bool Renderer::Init() {
    // Create context
    const auto context = SDL_GL_CreateContext(mWindow);
    if (!context) {
        SDL_Log("[RENDERER] Failed to create OpenGL context.");
        return false;
    }
    mContext.reset(context);

    // Init GLAD
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
        SDL_Log("[RENDERER] Failed to init GLAD.");
        return false;
    }

    // Set Vsync
    if (SDL_GL_SetSwapInterval(1) < 0) {
        SDL_Log("[RENDERER] Failed to set VSync: %s", SDL_GetError());
        return false;
    }

    // Set clear color
    glClearColor(CLEAR_COLOR.x, CLEAR_COLOR.y, CLEAR_COLOR.z, CLEAR_COLOR.w);
    return true;
}

void Renderer::Draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(mWindow);
}