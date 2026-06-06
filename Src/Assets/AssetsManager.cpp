#include "AssetsManager.h"
#include "CampfireEngine/Graphics/Resources/Texture.h"

AssetsManager::AssetsManager() = default;
AssetsManager::~AssetsManager() = default;

void AssetsManager::UnloadData() {
    UnloadTextures();
}

Texture* AssetsManager::GetTexture(const std::string& name) {
    if (const auto it  = mTextures.find(name); it != mTextures.end()) {
        return it->second.get();
    }

    auto uniqueTexture = std::make_unique<Texture>();
    mTextures[name] = std::move(uniqueTexture);

    return mTextures[name].get();
}

void AssetsManager::RemoveTexture(const std::string &name) {
    if (const auto it  = mTextures.find(name); it != mTextures.end()) {
        mTextures.erase(it);
    }
}

void AssetsManager::UnloadTextures() {
    mTextures.clear();
}