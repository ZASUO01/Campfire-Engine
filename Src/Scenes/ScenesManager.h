#pragma once
#include <memory>
#include <thread>
#include "CampfireEngine/Subsystems/ScenesSystem.h"

class ScenesManager : public ScenesSystem {
public:
    enum class State {
        IDLE,
        LOADING,
        LOADED,
        READY
    };

    explicit ScenesManager(class GameBase* mGame);
    ~ScenesManager() override;

    void SetCurrentScene(std::unique_ptr<Scene> newScene) override;
    void UpdateState();

    [[nodiscard]] State GetSceneState() const { return mState.load(); }

private:
    std::unique_ptr<Scene> mCurrentScene;
    std::unique_ptr<Scene> mNextScene;

    std::jthread mLoadingThread;
    std::atomic<State> mState;

    GameBase* mGame;
};


