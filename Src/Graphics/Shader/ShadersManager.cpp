#include "ShadersManager.h"
#include "CampfireEngine/Graphics/Shader/Shader.h"

ShadersManager::~ShadersManager() = default;

Shader *ShadersManager::GetShader(const std::string &name) {
    if (const auto it = mShaders.find(name); it != mShaders.end()) {
        return it->second.get();
    }

    auto uniqueShader = std::make_unique<Shader>();
    mShaders[name] = std::move(uniqueShader);

    return mShaders[name].get();
}

void ShadersManager::RemoveShader(const std::string &name) {
    if (const auto it = mShaders.find(name); it != mShaders.end()) {
        mShaders.erase(it);
    }
}

void ShadersManager::UnloadShaders() {
    mShaders.clear();
}