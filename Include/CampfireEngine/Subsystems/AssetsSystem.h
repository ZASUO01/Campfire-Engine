#pragma once
#include <string>

class AssetsSystem {
public:
    virtual ~AssetsSystem() = default;

    virtual void UnloadData() = 0;

    virtual class Texture* GetTexture(const std::string& name) = 0;
    virtual void RemoveTexture(const std::string& name) = 0;
    virtual void UnloadTextures() = 0;
};
