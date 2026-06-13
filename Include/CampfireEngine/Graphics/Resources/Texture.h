#pragma once
#include "CampfireEngine/Types/SDLTypesFwd.h"

class Texture {
public:
    Texture();
    ~Texture();

    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    void CreateFromSurface(UniqueSurface&& surface);

    void SetActive(int index = 0) const;
    [[nodiscard]] bool IsValid() const { return mTextureID != 0; }

    [[nodiscard]] int GetWidth() const { return mWidth; }
    [[nodiscard]] int GetHeight() const { return mHeight; }

    [[nodiscard]] unsigned int GetID() const { return mTextureID; }

private:
    void Destroy();

    unsigned int mTextureID;
    int mWidth;
    int mHeight;
};