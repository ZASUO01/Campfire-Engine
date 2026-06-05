#include "Renderer.h"
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include "Utils/SDLUtils.h"
#include "Graphics/PostEffect/PostEffectsManager.h"
#include "Graphics/PostEffect/FrameBuffer.h"
#include "Drawer.h"

Renderer::Renderer(SDL_Window *window, const int width, const int height)
:mScreenWidth(width)
,mScreenHeight(height)
,mWindow(window)
,mDrawer(nullptr)
,mFrameBuffer(nullptr)
,mPostEffectCommand({})
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

    mFrameBuffer = std::make_unique<FrameBuffer>(mScreenWidth, mScreenHeight);

    mDrawer = std::make_unique<Drawer>();

    // Set clear color
    glClearColor(CLEAR_COLOR.x, CLEAR_COLOR.y, CLEAR_COLOR.z, CLEAR_COLOR.w);
    return true;
}

void Renderer::SetRenderTarget(const RenderTarget target) const {
    if (target == RenderTarget::PostProcess) {
        mFrameBuffer->Bind();
        return;
    }

    FrameBuffer::Unbind();
}

void Renderer::Clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw() {

}

void Renderer::PostDraw() const {
    const auto tex = mFrameBuffer->GetTexture();

    mDrawer->DrawPostPass(mPostEffectCommand, tex);
}

void Renderer::Present() const {
    SDL_GL_SwapWindow(mWindow);
}
