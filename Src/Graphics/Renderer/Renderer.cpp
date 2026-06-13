#include "Renderer.h"
#include "Drawer.h"
#include "CampfireEngine/Utils/SDLUtils.h"
#include <glad/glad.h>
#include <SDL2/SDL.h>

Renderer::Renderer(SDL_Window* window, const int width, const int height)
:mContext(nullptr)
,mWindow(window)
,mWindowWidth(width)
,mWindowHeight(height)
,mOrthoMatrix(Matrix4::Identity)
,mDrawer(nullptr)
{}

Renderer::~Renderer() = default;

bool Renderer::Init() {
    const auto context = SDL_GL_CreateContext(mWindow);
    if (!context) {
        SDL_Log("[RENDERER] Failed to create OpenGL context.");
        return false;
    }
    mContext.reset(context);

    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
        SDL_Log("[RENDERER] Failed to init GLAD.");
        return false;
    }

    // Set Vsync
    if (SDL_GL_SetSwapInterval(1) < 0) {
        SDL_Log("[RENDERER] Failed to set VSync: %s", SDL_GetError());
        return false;
    }

    glClearColor(CLEAR_COLOR.x, CLEAR_COLOR.y, CLEAR_COLOR.z, CLEAR_COLOR.w);


    // Set matrices default
    mOrthoMatrix = Matrix4::CreateOrtho(0.0f, static_cast<float>(mWindowWidth), static_cast<float>(mWindowHeight), 0.0f, -1.0f, 1.0f);

    // Init members
    mDrawer = std::make_unique<Drawer>();

    return true;
}

void Renderer::SetRenderTarget(RenderTarget target) {

}

void Renderer::Clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw() {
    mDrawer->DrawUIPass(mUICommandsQueue, mOrthoMatrix);
}

void Renderer::Present() const {
    SDL_GL_SwapWindow(mWindow);
}
