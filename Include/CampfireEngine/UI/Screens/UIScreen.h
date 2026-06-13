#pragma once
#include <memory>
#include <vector>

#include "CampfireEngine/Context/CoreContext.h"

class UIScreen {
public:
    enum class ScreenState {
        Inactive,
        Active,
        Paused,
        Closing
    };

    explicit UIScreen();
    virtual ~UIScreen();

    [[nodiscard]] ScreenState GetState() const { return mState; }

    class UIRect* AddRect(std::unique_ptr<UIRect> rect);
    class UIImage* AddImage(std::unique_ptr<UIImage> image);
    class UIText* AddText(std::unique_ptr<UIText> text);

    void Close();
protected:
    virtual void OnStart(const CoreContext& ctx) = 0;
    virtual void OnPause() {}
    virtual void OnResume() {}
    virtual void OnClose() {}

private:
    virtual void ProcessInput(int key) = 0;
    virtual void Update(float deltaTime) = 0;
    void SendDrawCommands(class RenderSubsystem* renderer) const;

    void Start(const CoreContext& ctx);
    void Pause();
    void Resume();

    std::vector<std::unique_ptr<UIRect>> mRectElements;
    std::vector<std::unique_ptr<UIImage>> mImageElements;
    std::vector<std::unique_ptr<UIText>> mTextElements;

    ScreenState mState;

friend class UIManager;
};
