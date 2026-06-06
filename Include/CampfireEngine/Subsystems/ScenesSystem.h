#pragma once
#include <memory>

class ScenesSystem {
public:
    virtual ~ScenesSystem() = default;
    virtual void SetCurrentScene(std::unique_ptr<class Scene> newScene) = 0;
};
