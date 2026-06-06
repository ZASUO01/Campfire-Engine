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
    [[nodiscard]] AssetsSystem& GetAssetsSystem() const;
    [[nodiscard]] PostEffectsSystem& GetPostEffectsSystem() const;
    [[nodiscard]] SynthesizerSystem& GetSynthesizerSystem() const;

protected:
    // Lifecycle methods
    [[nodiscard]] virtual bool Setup() = 0;
    virtual void Update(float deltaTime) = 0;
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

    // Renderer System
    std::unique_ptr<Renderer> mRenderer;

    // Resource management systems
    std::unique_ptr<ShadersManager> mShadersManager;
    std::unique_ptr<AssetsManager> mAssetsManager;
    std::unique_ptr<PostEffectsManager> mPostEffectsManager;
    std::unique_ptr<Synthesizer> mSynthesizer;

    // Game control variables
    GameState mGameState;
    bool mIsRunning;
    uint32_t mTicksCount;
};
