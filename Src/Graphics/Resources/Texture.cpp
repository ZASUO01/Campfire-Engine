#include "CampfireEngine/Graphics/Resources/Texture.h"

Texture::Texture()
:mTextureID(0)
,mWidth(0)
,mHeight(0)
{}

Texture::~Texture() {
    Destroy();
}

void Texture::CreateEmpty(const int width, const int height, const GLint internalFormat, const GLenum format) {
    mWidth = width;
    mHeight = height;

    if (mTextureID != 0) {
        glDeleteTextures(1, &mTextureID);
    }

    glGenTextures(1, &mTextureID);
    glBindTexture(GL_TEXTURE_2D, mTextureID);

    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
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