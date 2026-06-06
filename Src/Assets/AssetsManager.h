#pragma once
#include <memory>
#include <unordered_map>
#include "CampfireEngine/Subsystems/AssetsSystem.h"

class AssetsManager : public AssetsSystem {
public:
    AssetsManager();
    ~AssetsManager() override;

    void UnloadData() override;

    Texture* GetTexture(const std::string& name) override;
    void RemoveTexture(const std::string& name) override;
    void UnloadTextures() override;

private:
    std::unordered_map<std::string, std::unique_ptr<Texture>> mTextures;
};

