#include "Renderer.h"
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include "Utils/SDLUtils.h"
#include "Graphics/PostEffect/PostEffectsManager.h"
#include "Graphics/PostEffect/FrameBuffer.h"
#include "Drawer.h"
#include "CampfireEngine/Graphics/PostEffect/PostEffect.h"

Renderer::Renderer(SDL_Window *window, const int width, const int height)
:mScreenWidth(width)
,mScreenHeight(height)
,mWindow(window)
,mDrawer(nullptr)
,mPostEffectsManager(nullptr)
,mFrameBuffer(nullptr)
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

    mPostEffectsManager = std::make_unique<PostEffectsManager>();
    mFrameBuffer = std::make_unique<FrameBuffer>(mScreenWidth, mScreenHeight);

    mDrawer = std::make_unique<Drawer>();

    // Set clear color
    glClearColor(CLEAR_COLOR.x, CLEAR_COLOR.y, CLEAR_COLOR.z, CLEAR_COLOR.w);
    return true;
}

void Renderer::Draw() {
    // Enable frame buffer to draw elements and apply post effects later if enabled
    if (mPostEffectsManager->CanUseEffects()) {
        mFrameBuffer->Bind();
    }
    glClear(GL_COLOR_BUFFER_BIT);

    // Apply post effect case enabled
    if (mPostEffectsManager->CanUseEffects()) {
        FrameBuffer::Unbind();
        glClear(GL_COLOR_BUFFER_BIT);

        mDrawer->DrawPostPass(mPostEffectsManager->GetCurrentEffect(), mFrameBuffer->GetTexture());
   }

    // Swap back buffer to front
    SDL_GL_SwapWindow(mWindow);
}