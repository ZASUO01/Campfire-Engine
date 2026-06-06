#include "CampfireEngine/GameBase.h"
#include <SDL2/SDL.h>
#include "Utils/SDLUtils.h"
#include "CampfireEngine/Core/GameData.h"
#include "Graphics/Renderer/Renderer.h"
#include "Graphics/Shader/ShadersManager.h"
#include <memory>
#include "CampfireEngine/Graphics/PostEffect/PostEffect.h"
#include "CampfireEngine/Math/Random.h"
#include "Graphics/PostEffect/PostEffectsManager.h"
#include "Assets/AssetsManager.h"
#include "CampfireEngine/Scenes/Scene.h"
#include "Sound/Synthesizer.h"
#include "Scenes/ScenesManager.h"

GameBase::GameBase()
:mWindow(nullptr)
,mGameData(nullptr)
,mRenderer(nullptr)
,mScenesManager(nullptr)
,mShadersManager(nullptr)
,mAssetsManager(nullptr)
,mPostEffectsManager(nullptr)
,mSynthesizer(nullptr)
,mGameState(GameState::DOWN)
,mIsRunning(false)
,mTicksCount(0)
{}

GameBase::~GameBase() = default;

bool GameBase::Init()  {
    if (mGameState != GameState::DOWN) {
        SDL_Log("The game must be down first to be initialized then");
        return false;
    }
    mGameState = GameState::STARTING;

    if (!SDLUtils::SetupSubSystems()) {
        SDL_Log("Failed to setup subsystems");
        return false;
    }

    if (!SetupBase()) {
        SDL_Log("Failed to setup game base");
        return false;
    }

    if (!Setup()) {
        SDL_Log("Failed to setup game");
        return false;
    }

    mGameState = GameState::UP;
    return true;
}

void GameBase::RunLoop() {
    if (mGameState != GameState::UP) {
        return;
    }

    mIsRunning = true;
    mTicksCount = SDL_GetTicks();

    while (mIsRunning) {
        const uint32_t frameStartTicks = SDL_GetTicks();
        float deltaTime = static_cast<float>(frameStartTicks - mTicksCount) / 1000.0f;

        if (deltaTime > 0.05f){
            deltaTime = 0.05f;
        }
        mTicksCount = frameStartTicks;

        mScenesManager->UpdateState();

        switch (mScenesManager->GetSceneState()) {
            case ScenesManager::State::IDLE:
                // IDLE
                break;
            case ScenesManager::State::LOADING:
            case ScenesManager::State::LOADED:
                // LOADING
                break;
            case ScenesManager::State::READY:
                ProcessInput();
                UpdateGameBase(deltaTime);
                GenerateOutput();
                break;
            default:
                break;
        }



        const Uint32 frameElapsedTicks = SDL_GetTicks() - frameStartTicks;

        if (constexpr Uint32 targetMs = 1000 / 60; frameElapsedTicks < targetMs) {
            const Uint32 sleepTime = targetMs - frameElapsedTicks;
            SDL_Delay(sleepTime);
        }
    }
}

void GameBase::Shutdown() {
    if (mGameState == GameState::DOWN) {
        return;
    }

    CleanUp();
    CleanUpBase();

    SDLUtils::ShutdownSubSystems();
}

RendererSystem &GameBase::GetRendererSystem() const {
    return *mRenderer;
}

ScenesSystem &GameBase::GetScenesSystem() const {
    return *mScenesManager;
}

ShadersSystem& GameBase::GetShadersSystem() const {
    return *mShadersManager;
}

AssetsSystem &GameBase::GetAssetsSystem() const {
    return *mAssetsManager;
}

PostEffectsSystem &GameBase::GetPostEffectsSystem() const {
    return *mPostEffectsManager;
}

SynthesizerSystem &GameBase::GetSynthesizerSystem() const {
    return *mSynthesizer;
}

void SDLWindowDeleter::operator()(SDL_Window* window) const{
    SDLUtils::SDLWindowDeleter()(window);
}

bool GameBase::SetupBase() {
    Random::Init();

    // Init Game data
    mGameData = std::make_unique<GameData>();

    //System window
    SDL_Window* window = SDL_CreateWindow(
        mGameData->GetMainConfig().WINDOW_TITLE.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        mGameData->GetMainConfig().WINDOW_WIDTH,
        mGameData->GetMainConfig().WINDOW_HEIGHT,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );

    if (!window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }
    mWindow.reset(window);

    // Create renderer
    mRenderer = std::make_unique<Renderer>(mWindow.get(), mGameData->GetMainConfig().WINDOW_WIDTH,
                                           mGameData->GetMainConfig().WINDOW_HEIGHT);
    if (!mRenderer->Init()) {
        SDL_Log("Failed to initialize renderer");
        return false;
    }

    mScenesManager = std::make_unique<ScenesManager>(this);
    mShadersManager = std::make_unique<ShadersManager>();
    mAssetsManager = std::make_unique<AssetsManager>();
    mPostEffectsManager = std::make_unique<PostEffectsManager>();
    mSynthesizer = std::make_unique<Synthesizer>();
    if (!mSynthesizer->Init()) {
        SDL_Log("Failed to initialize synthesizer");
        return false;
    }

    return true;
}

void GameBase::CleanUpBase() {
    mSynthesizer.reset();
    mPostEffectsManager.reset();
    mAssetsManager.reset();
    mShadersManager.reset();
    mRenderer.reset();
    mWindow.reset();
    mGameData.reset();
}

void GameBase::ProcessInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                Quit();
                break;
            default:
                break;
        }
    }
}

void GameBase::UpdateGameBase(const float deltaTime) {
    if (mPostEffectsManager->CanUseEffects()) {
        mPostEffectsManager->GetCurrentEffect()->Update(deltaTime, mRenderer.get());
    }

    mSynthesizer->Update();

    Update(deltaTime);
}

void GameBase::GenerateOutput() const {
    if (mPostEffectsManager->CanUseEffects()) {
        mRenderer->SetRenderTarget(Renderer::RenderTarget::PostProcess);
    }
    Renderer::Clear();

    mRenderer->Draw();

    if (mPostEffectsManager->CanUseEffects()) {
        mRenderer->SetRenderTarget(Renderer::RenderTarget::Screen);
        Renderer::Clear();
        mRenderer->PostDraw();
    }
    mRenderer->Present();
}

