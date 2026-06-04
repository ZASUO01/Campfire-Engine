#pragma once
#include "Types/SDLTypesFwd.h"
#include "Types/TypesFwd.h"

class GameBase {
public:
    GameBase();
    virtual ~GameBase();

    [[nodiscard]] bool Init();
    void RunLoop();
    void Quit() { mIsRunning = false;}
    void Shutdown();

    // Getters
    [[nodiscard]] Renderer* GetRenderer() const { return mRenderer.get(); }
    [[nodiscard]] ShadersManager* GetShadersManager() const { return mShadersManager.get(); }

protected:
    // Lifecycle methods
    [[nodiscard]] virtual bool Setup() = 0;
    virtual void CleanUp() = 0;

private:
    enum class GameState {
        DOWN,
        STARTING,
        UP,
    };

    // Lifecycle methods
    [[nodiscard]] bool SetupBase();
    void CleanUpBase();

    // Looping operations
    void ProcessInput();
    void UpdateGameBase(float deltaTime);
    void GenerateOutput() const;

    // System window
    UniqueSDLWindow mWindow;

    // Game configuration
    std::unique_ptr<GameData> mGameData;

    // Renderer
    std::unique_ptr<Renderer> mRenderer;

    // Resource managers
    std::unique_ptr<ShadersManager> mShadersManager;

    // Game control variables
    GameState mGameState;
    bool mIsRunning;
    uint32_t mTicksCount;
};