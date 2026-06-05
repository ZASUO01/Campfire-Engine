#pragma once
#include "CampfireEngine/Types/SDLTypesFwd.h"
#include "CampfireEngine/Types/TypesFwd.h"

class GameBase {
public:
    GameBase();
    virtual ~GameBase();

    [[nodiscard]] bool Init();
    void RunLoop();
    void Quit() { mIsRunning = false;}
    void Shutdown();

    // Getters
    [[nodiscard]] RendererSystem& GetRendererSystem() const;
    [[nodiscard]] ShadersSystem& GetShadersSystem() const;
    [[nodiscard]] PostEffectsSystem& GetPostEffectsSystem() const;

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
    void UpdateGameBase(float deltaTime) const;
    void GenerateOutput() const;

    // System window
    UniqueSDLWindow mWindow;

    // Game configuration
    std::unique_ptr<GameData> mGameData;

    // Renderer System
    std::unique_ptr<Renderer> mRenderer;

    // Resource management systems
    std::unique_ptr<ShadersManager> mShadersManager;
    std::unique_ptr<PostEffectsManager> mPostEffectsManager;

    // Game control variables
    GameState mGameState;
    bool mIsRunning;
    uint32_t mTicksCount;
};
