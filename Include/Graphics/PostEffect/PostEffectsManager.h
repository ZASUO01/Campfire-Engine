#pragma once
#include <memory>
#include <unordered_map>

class PostEffectsManager {
public:
    PostEffectsManager();
    ~PostEffectsManager();

    [[nodiscard]] bool CanUseEffects() const { return mCurrentEffect != nullptr; }

    class PostEffect* GetCurrentEffect() const { return mCurrentEffect; }
    PostEffect* GetEffect(const std::string& name) const;

    void SetCurrentEffect(const std::string& name);
    void DeactivateCurrentEffect() { mCurrentEffect = nullptr; }

    void PushEffect(std::unique_ptr<PostEffect> effect);
    void RemoveEffect(const std::string& name);
    void ClearEffects();

private:
    PostEffect* mCurrentEffect;
    std::pmr::unordered_map<std::string, std::unique_ptr<PostEffect>> mPostEffects;
};
