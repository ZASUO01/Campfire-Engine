#pragma once
#include "CampfireEngine/Math/Math.h"
#include "CampfireEngine/Subsystems/RendererSystem.h"
#include "CampfireEngine/Types/SDLTypesFwd.h"

class Renderer : public RendererSystem{
public:
    Renderer(SDL_Window* window, int width, int height);
    ~Renderer() override;

    [[nodiscard]] bool Init();
    void Draw() override;

    [[nodiscard]] class PostEffectsManager* GetPostEffectsManager() const { return mPostEffectsManager.get(); }
private:
    int mScreenWidth;
    int mScreenHeight;

    SDL_Window* mWindow;
    UniqueGLContext mContext;

    // Operator that draws elements
    std::unique_ptr<class Drawer> mDrawer;

    // Post effects management
    std::unique_ptr<PostEffectsManager> mPostEffectsManager;
    std::unique_ptr<class FrameBuffer> mFrameBuffer;

    // Constants
    static constexpr Vector4 CLEAR_COLOR{0.45f, 0.55f, 0.60f, 1.0f};
};