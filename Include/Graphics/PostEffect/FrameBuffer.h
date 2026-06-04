#pragma once
#include <memory>

class FrameBuffer {
public:
    FrameBuffer(int width, int height);
    ~FrameBuffer();

    FrameBuffer(const FrameBuffer&) = delete;
    FrameBuffer& operator=(const FrameBuffer&) = delete;

    void Bind() const;
    static void Unbind();

    [[nodiscard]] class Texture* GetTexture() const { return  mTexture.get(); }
private:
    unsigned int mFBO;
    unsigned int mRBO;

    std::unique_ptr<Texture> mTexture;
};
