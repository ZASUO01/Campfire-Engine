#pragma once
#include "Math/Math.h"
#include "Types/SDLTypesFwd.h"

class Renderer {
public:
    Renderer(SDL_Window* window, int width, int height);
    ~Renderer();

    [[nodiscard]] bool Init();
    void Draw();

private:
    int mScreenWidth;
    int mScreenHeight;

    SDL_Window* mWindow;
    UniqueGLContext mContext;

    // Constants
    static constexpr Vector4 CLEAR_COLOR{0.45f, 0.55f, 0.60f, 1.0f};
};