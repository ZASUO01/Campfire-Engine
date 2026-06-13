#pragma once
#include "CampfireEngine/Types/SDLTypesFwd.h"
#include "RenderUtils.h"
#include "CampfireEngine/Context/Subsystems/RenderSubsystem.h"
#include "CampfireEngine/Math/Math.h"

class Renderer : public RenderSubsystem {
public:
    enum class RenderTarget {
        Screen,
        Buffer
    };

    Renderer(SDL_Window* window, int width, int height);
    ~Renderer() override;

    [[nodiscard]] bool Init();

    void SetRenderTarget(RenderTarget target);
    static void Clear();
    void Draw();
    void Present() const;

    void SetOrthoMatrix(const Matrix4& matrix) { mOrthoMatrix = matrix; }

    void PushUICommand(const RenderUtils::SpriteCommand &command) override { mUICommandsQueue.emplace_back(command); }
private:
    // SDL structs
    UniqueGLContext mContext;
    SDL_Window* mWindow;

    // Window parameters
    int mWindowWidth;
    int mWindowHeight;

    // Visualisation matrices
    Matrix4 mOrthoMatrix;

    // Drawer member has drawing methods
    std::unique_ptr<class Drawer> mDrawer;

    std::vector<RenderUtils::SpriteCommand> mUICommandsQueue;

    // constants
    static constexpr Vector4 CLEAR_COLOR{0.45f, 0.55f, 0.60f, 1.0f};
};