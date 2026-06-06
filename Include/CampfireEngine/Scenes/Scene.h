#pragma once
#include <stop_token>

class Scene {
public:
    virtual ~Scene() = default;

protected:
    virtual void OnInit(class ScenesSystem* system) = 0;
    virtual void OnPostInit(ScenesSystem* system, class GameBase* game) = 0;
    virtual void OnExit(GameBase* game) = 0;

    [[nodiscard]] bool IsStopped() const { return  mStopToken.stop_requested(); }

private:
    std::stop_token mStopToken;

    void InternalInit(const std::stop_token& st, ScenesSystem* system) {
        mStopToken = st;
        OnInit(system);
    }

friend class ScenesManager;
};
