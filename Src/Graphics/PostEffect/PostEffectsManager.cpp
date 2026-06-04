#include "Graphics/PostEffect/PostEffectsManager.h"
#include "Graphics/PostEffect/PostEffect.h"

PostEffectsManager::PostEffectsManager()
:mCurrentEffect(nullptr)
{}

PostEffectsManager::~PostEffectsManager() {
    ClearEffects();
}


PostEffect *PostEffectsManager::GetEffect(const std::string& name) const {
    if (const auto it = mPostEffects.find(name); it != mPostEffects.end()) {
        return it->second.get();
    }

    return nullptr;
}

void PostEffectsManager::SetCurrentEffect(const std::string& name) {
    if (const auto it = mPostEffects.find(name); it != mPostEffects.end()) {
        mCurrentEffect = it->second.get();
    }
}

void PostEffectsManager::PushEffect(std::unique_ptr<PostEffect> effect) {
    const std::string  name = effect->GetName();
    mPostEffects[name] = std::move(effect);
    mCurrentEffect = mPostEffects[name].get();
}

void PostEffectsManager::RemoveEffect(const std::string& name) {
    if (const auto it = mPostEffects.find(name); it != mPostEffects.end()) {
        if (it->second.get() == mCurrentEffect) {
            mCurrentEffect = nullptr;
        }

        mPostEffects.erase(name);
    }
}

void PostEffectsManager::ClearEffects() {
    mPostEffects.clear();
}
