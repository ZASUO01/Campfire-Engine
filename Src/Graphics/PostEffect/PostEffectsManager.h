#pragma once
#include <memory>
#include <unordered_map>
#include "CampfireEngine/Subsystems/PostEffectsSystem.h"

class PostEffectsManager : public PostEffectsSystem {
public:
    PostEffectsManager();
    ~PostEffectsManager() override;

    PostEffect* GetCurrentEffect() const override { return mCurrentEffect; }
    PostEffect* GetEffect(const std::string& name) const override;

    void SetCurrentEffect(const std::string& name) override;
    void DeactivateCurrentEffect() override { mCurrentEffect = nullptr; }

    void PushEffect(std::unique_ptr<PostEffect> effect) override;
    void RemoveEffect(const std::string& name) override;
    void ClearEffects() override;

    [[nodiscard]] bool CanUseEffects() const { return mCurrentEffect != nullptr; }
private:
    PostEffect* mCurrentEffect;
    std::pmr::unordered_map<std::string, std::unique_ptr<PostEffect>> mPostEffects;
};
