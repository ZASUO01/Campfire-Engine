#pragma once
#include "TypesFwd.h"

class GameBase {
public:
    GameBase();
    virtual ~GameBase();

    [[nodiscard]] bool Init();
    void RunLoop();
    void Quit() { mIsRunning = false;}
    void Shutdown();

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
    void GenerateOutput();

    // System window
    UniqueSDLWindow mWindow;

    // Game control variables
    GameState mGameState;
    bool mIsRunning;
    uint32_t mTicksCount;
};