#pragma once
#include "Types/TypesFwd.h"
#include "Types/SDLTypesFwd.h"

class Engine{
public:
    Engine();
    virtual ~Engine();

    // Lifecycle operations
    [[nodiscard]] bool Init();
    void RunLoop();
    void Quit() { mIsRunning = false; }
    void Shutdown();

    [[nodiscard]] ConfigSubsystem* GetConfigSubsystem() const;
    [[nodiscard]] AssetsSubsystem* GetAssetsSubSystem() const;
    [[nodiscard]] ShadersSubsystem* GetShadersSubsystem() const;
    [[nodiscard]] RenderSubsystem* GetRenderSubsystem() const;

    [[nodiscard]] UISubsystem* GetUISubsystem() const;

protected:
    [[nodiscard]] virtual bool Setup() = 0;
    virtual void Update(float deltaTime) = 0;

private:
    enum class State {
        DOWN,
        STARTING,
        UP,
    };

    [[nodiscard]] bool SetupEngine();
    void CleanUp();

    // Looping Operations
    void ProcessInput();
    void UpdateEngine(float deltaTime);
    void GenerateOutput();

    // Operating System window
    UniqueSDLWindow mWindow;

    // Engine subsystems
    std::unique_ptr<EngineConfig> mConfig;
    std::unique_ptr<AssetsManager> mAssetManager;
    std::unique_ptr<ShadersManager> mShadersManager;
    std::unique_ptr<Renderer> mRenderer;
    std::unique_ptr<UIManager> mUIManager;

    // Control variables
    uint32_t mTicksCount;
    bool mIsRunning;
    State mState;
};
