#include "CampfireEngine/Graphics/Resources/Texture.h"
#include <glad/glad.h>
#include "CampfireEngine/Utils/SDLUtils.h"
#include <SDL2/SDL.h>

Texture::Texture()
:mTextureID(0)
,mWidth(0)
,mHeight(0)
{}

Texture::~Texture() {
    Destroy();
}

void Texture::CreateFromSurface(UniqueSurface&& surface) {
    if (!surface) {
        return;
    }

    mWidth = surface->w;
    mHeight = surface->h;

    glGenTextures(1, &mTextureID);
    glBindTexture(GL_TEXTURE_2D, mTextureID);

    // ensure pixel alignment
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    const int pixelsPerLine = surface->pitch / surface->format->BytesPerPixel;

    glPixelStorei(GL_UNPACK_ROW_LENGTH, pixelsPerLine);

    // send data to the VRAM
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

    glBindTexture(GL_TEXTURE_2D, 0);
    surface.reset();
}

void Texture::SetActive(const int index) const {
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, mTextureID);
}

void Texture::Destroy() {
    if (mTextureID != 0) {
        glDeleteTextures(1, &mTextureID);
        mTextureID = 0;
    }
}
