#pragma once
#include <memory>
#include <string>

class PostEffectsSystem {
public:
    virtual ~PostEffectsSystem() = default;

    virtual void PushEffect(std::unique_ptr<class PostEffect> effect) = 0;
    virtual void RemoveEffect(const std::string& name) = 0;
    virtual void ClearEffects() = 0;

    virtual void SetCurrentEffect(const std::string& name) = 0;
    virtual void DeactivateCurrentEffect() = 0;

    [[nodiscard]] virtual PostEffect* GetCurrentEffect() const = 0;
    [[nodiscard]] virtual PostEffect* GetEffect(const std::string& name) const = 0;
};
