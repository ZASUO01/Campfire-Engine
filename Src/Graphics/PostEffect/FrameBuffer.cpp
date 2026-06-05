#include "FrameBuffer.h"
#include "CampfireEngine/Graphics/Resources/Texture.h"
#include <glad/glad.h>
#include <SDL2/SDL_log.h>

FrameBuffer::FrameBuffer(const int width, const int height)
:mFBO(0)
,mRBO(0)
{
    glGenFramebuffers(1, &mFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, mFBO);

    mTexture = std::make_unique<Texture>();
    mTexture->CreateEmpty(width, height);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTexture->GetID(), 0);

    glGenRenderbuffers(1, &mRBO);
    glBindRenderbuffer(GL_RENDERBUFFER, mRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, mRBO);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mRBO);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        SDL_Log("[FRAMEBUFFER] Failed to complete framebuffer initialization.");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FrameBuffer::~FrameBuffer() {
    if (mFBO) {
        glDeleteFramebuffers(1, &mFBO);
    }

    if (mRBO) {
        glDeleteRenderbuffers(1, &mRBO);
    }
}

void FrameBuffer::Bind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
}

void FrameBuffer::Unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}