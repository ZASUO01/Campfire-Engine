#pragma once
#include "RendererUtils.h"
#include "CampfireEngine/Math/Math.h"
#include "CampfireEngine/Subsystems/RendererSystem.h"
#include "CampfireEngine/Types/SDLTypesFwd.h"

class Renderer : public RendererSystem{
public:
    enum class RenderTarget {
        Screen,
        PostProcess
    };

    Renderer(SDL_Window* window, int width, int height);
    ~Renderer() override;

    [[nodiscard]] bool Init();

    // Rendering functions
    void SetRenderTarget(RenderTarget target) const;
    static void Clear();
    void Draw();
    void PostDraw() const;
    void Present() const;

    // queue functions
    void SetPostEffectCommand(const RendererUtils::PostEffectCommand& cmd) override { mPostEffectCommand = cmd; }
private:
    int mScreenWidth;
    int mScreenHeight;

    SDL_Window* mWindow;
    UniqueGLContext mContext;

    // Operator that draws elements
    std::unique_ptr<class Drawer> mDrawer;

    // Post effects management
    std::unique_ptr<class FrameBuffer> mFrameBuffer;

    //Current post effect command
    RendererUtils::PostEffectCommand mPostEffectCommand;

    // Constants
    static constexpr Vector4 CLEAR_COLOR{0.45f, 0.55f, 0.60f, 1.0f};
};