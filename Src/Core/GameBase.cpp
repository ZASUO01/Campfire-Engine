#include "GameBase.h"
#include <memory>
#include <SDL2/SDL.h>
#include "Utils/SDLUtils.h"
#include "Core/GameData.h"
#include "Graphics/Renderer/Renderer.h"
#include "Graphics/Shader/Shader.h"
#include "Graphics/Shader/ShadersManager.h"
#include "Math/Random.h"

GameBase::GameBase()
:mWindow(nullptr)
,mGameData(nullptr)
,mRenderer(nullptr)
,mShadersManager(nullptr)
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

        ProcessInput();
        UpdateGameBase(deltaTime);
        GenerateOutput();

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

    mShadersManager = std::make_unique<ShadersManager>();

    return true;
}

void GameBase::CleanUpBase() {
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
    // TODO
}

void GameBase::GenerateOutput() const {
    mRenderer->Draw();
}

