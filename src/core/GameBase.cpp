#include "core/GameBase.h"
#include "utils/SDLUtils.h"
#include <SDL2/SDL.h>

GameBase::GameBase()
:mWindow(nullptr)
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
    //System window
    SDL_Window* window = SDL_CreateWindow(
        "Campfire Engine",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1024,
        768,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );

    if (!window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }
    mWindow.reset(window);

    return true;
}

void GameBase::CleanUpBase() {

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

void GameBase::GenerateOutput() {
    // TODO
}

