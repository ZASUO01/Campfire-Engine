#include "CampfireEngine/Engine.h"
#include "Utils/SDLControl.h"
#include "CampfireEngine/Data/EngineConfig.h"
#include "Graphics/Renderer/Renderer.h"
#include "Graphics/Shader/ShadersManager.h"
#include "UI/UIManager.h"
#include "Assets/AssetsManager.h"
#include <SDL2/SDL.h>

Engine::Engine()
:mWindow(nullptr)
,mConfig(nullptr)
,mAssetManager(nullptr)
,mShadersManager(nullptr)
,mRenderer(nullptr)
,mUIManager(nullptr)
,mTicksCount(0)
,mIsRunning(false)
,mState(State::DOWN)
{}

Engine::~Engine() = default;

bool Engine::Init() {
    if (mState != State::DOWN) {
        return false;
    }
    mState = State::STARTING;

    if (!SDLControl::InitSubsystems()) {
        return false;
    }

    if (!SetupEngine()) {
        return false;
    }

    if (!Setup()) {
        return false;
    }

    mState = State::UP;
    return true;
}

void Engine::RunLoop() {
    if (mState != State::UP) {
        return;
    }

    mTicksCount = SDL_GetTicks();
    mIsRunning = true;

    while (mIsRunning) {
        const uint32_t frameStartTicks = SDL_GetTicks();
        float deltaTime = static_cast<float>(frameStartTicks - mTicksCount) / 1000.0f;

        if (deltaTime > 0.05f){
            deltaTime = 0.05f;
        }
        mTicksCount = frameStartTicks;

        ProcessInput();
        UpdateEngine(deltaTime);
        GenerateOutput();

        const Uint32 frameElapsedTicks = SDL_GetTicks() - frameStartTicks;

        if (constexpr Uint32 targetMs = 1000 / 60; frameElapsedTicks < targetMs) {
            const Uint32 sleepTime = targetMs - frameElapsedTicks;
            SDL_Delay(sleepTime);
        }
    }
}

void Engine::Shutdown() {
    CleanUp();
}

ConfigSubsystem *Engine::GetConfigSubsystem() const {
    return mConfig.get();
}

AssetsSubsystem *Engine::GetAssetsSubSystem() const {
    return mAssetManager.get();
}

ShadersSubsystem *Engine::GetShadersSubsystem() const {
    return mShadersManager.get();
}

RenderSubsystem *Engine::GetRenderSubsystem() const {
    return mRenderer.get();
}

UISubsystem *Engine::GetUISubsystem() const {
    return mUIManager.get();
}

bool Engine::SetupEngine() {
    mConfig = std::make_unique<EngineConfig>();

    mWindow = UniqueSDLWindow(SDL_CreateWindow(
        mConfig->GetWindowConfig().title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        mConfig->GetWindowConfig().width,
        mConfig->GetWindowConfig().height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN));
    if (!mWindow) {
        SDL_Log("Failed to create SDL_Window: %s", SDL_GetError());
        return false;
    }

    mRenderer = std::make_unique<Renderer>(mWindow.get(), mConfig->GetWindowConfig().width,
                                           mConfig->GetWindowConfig().height);
    if (!mRenderer->Init()) {
        SDL_Log("Failed to initialize Renderer");
        return false;
    }

    mShadersManager = std::make_unique<ShadersManager>();
    mAssetManager = std::make_unique<AssetsManager>();

    mUIManager = std::make_unique<UIManager>();
    if (!UIManager::Load({GetConfigSubsystem(), GetAssetsSubSystem(), GetShadersSubsystem()})) {
        return false;
    }

    return true;
}

void Engine::CleanUp() {
    SDLControl::ShutdownSubsystems();
}

void Engine::ProcessInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                Quit();
                break;
            case SDL_KEYDOWN:
                mUIManager->ProcessTopScreenInput(event.key.keysym.sym);
                break;
            default:
                break;
        }
    }
}

void Engine::UpdateEngine(const float deltaTime) {
    mUIManager->UpdateScreens(deltaTime);
    mUIManager->SendScreensDrawCommands(GetRenderSubsystem());

    Update(deltaTime);
}

void Engine::GenerateOutput() {
    Renderer::Clear();
    mRenderer->Draw();
    mRenderer->Present();
}
