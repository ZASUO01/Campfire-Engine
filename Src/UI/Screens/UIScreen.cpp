#include "CampfireEngine/UI/Screens/UIScreen.h"
#include "CampfireEngine/UI/Elements/UIImage.h"
#include "CampfireEngine/UI/Elements/UIRect.h"
#include "CampfireEngine/UI/Elements/UIText.h"

UIScreen::UIScreen()
:mState(ScreenState::Inactive)
{}

UIScreen::~UIScreen() = default;

UIRect* UIScreen::AddRect(std::unique_ptr<UIRect> rect) {
    mRectElements.emplace_back(std::move(rect));

    return mRectElements.back().get();
}

UIImage* UIScreen::AddImage(std::unique_ptr<UIImage> image) {
    mImageElements.emplace_back(std::move(image));

    return mImageElements.back().get();
}

UIText* UIScreen::AddText(std::unique_ptr<UIText> text) {
    mTextElements.emplace_back(std::move(text));

    return mTextElements.back().get();
}

void UIScreen::SendDrawCommands(RenderSubsystem* renderer) const {
    for (const auto& rect : mRectElements) {
        if (rect->IsVisible()) {
            rect->SendDrawCommand(renderer);
        }
    }

    for (const auto& image : mImageElements) {
        if (image->IsVisible()) {
            image->SendDrawCommand(renderer);
        }
    }

    for (const auto& text : mTextElements) {
        if (text->IsVisible()) {
            text->SendDrawCommand(renderer);
        }
    }
}

void UIScreen::Start(const CoreContext& ctx) {
    OnStart(ctx);
    mState = ScreenState::Active;
}

void UIScreen::Pause() {
    OnPause();
    mState = ScreenState::Paused;
}

void UIScreen::Resume() {
    OnResume();
    mState = ScreenState::Active;
}

void UIScreen::Close() {
    OnClose();
    mState = ScreenState::Closing;
}
