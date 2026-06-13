#pragma once
#include <string>

class AssetsSubsystem {
public:
    virtual ~AssetsSubsystem() = default;
    virtual class Texture* GetTexture(const std::string& name) = 0;
    virtual void RemoveTexture(const std::string& name) = 0;

    virtual class Font* GetFont(const std::string& name) = 0;
    virtual void RemoveFont(const std::string& name) = 0;
};
