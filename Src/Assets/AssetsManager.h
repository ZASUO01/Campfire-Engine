#pragma once
#include <memory>
#include <unordered_map>
#include "CampfireEngine/Context/Subsystems/AssetsSubsystem.h"

class AssetsManager : public AssetsSubsystem {
public:
    AssetsManager();
    ~AssetsManager() override;

    void UnloadData();

    Texture* GetTexture(const std::string& name) override;
    void RemoveTexture(const std::string& name) override;
    void UnloadTextures();

    Font* GetFont(const std::string& name) override;
    void RemoveFont(const std::string& name) override;
    void UnloadFonts();

private:
    std::unordered_map<std::string, std::unique_ptr<Texture>> mTextures;
    std::unordered_map<std::string, std::unique_ptr<Font>> mFonts;
};


