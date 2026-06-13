#include "UIManager.h"
#include "CampfireEngine/Graphics/Resources/Font.h"
#include "CampfireEngine/Graphics/Shader/Shader.h"
#include "CampfireEngine/UI/Screens/UIScreen.h"
#include "CampfireEngine/Utils/FileUtils.h"

UIManager::UIManager() = default;
UIManager::~UIManager() = default;

bool UIManager::Load(const CoreContext& ctx) {
    const auto shaderName = ctx.configCtx->GetUIConfig().UIShaderName;

    std::string vertexShaderString;
    if (!FileUtils::LoadFileToString(shaderName+".vert", vertexShaderString)) {
        return false;
    }

    std::string fragmentShaderString;
    if (!FileUtils::LoadFileToString(shaderName+".frag", fragmentShaderString)) {
        return false;
    }

    const auto shader = ctx.shaderCtx->GetShader(shaderName);
    if (!shader) {
        return false;
    }

    if (!shader->Build(vertexShaderString, fragmentShaderString)) {
        ctx.shaderCtx->RemoveShader(shaderName);
        return false;
    }

    const auto fontName = ctx.configCtx->GetUIConfig().UIFontName;
    const auto font = ctx.assetsCtx->GetFont(fontName);
    if (!font) {
        return false;
    }

    if (!font->Load(fontName)) {
        ctx.assetsCtx->RemoveFont(fontName);
        return false;
    }

    return true;
}

void UIManager::PushScreen(std::unique_ptr<UIScreen> screen, const CoreContext& ctx) {
    if (!screen) {
        return;
    }

    if (!mScreensStack.empty()) {
        mScreensStack.back()->Pause();
    }

    const auto screenPtr = screen.get();
    mScreensStack.emplace_back(std::move(screen));
    screenPtr->Start(ctx);
}

void UIManager::ProcessTopScreenInput(const int key) const {
    if (!mScreensStack.empty()) {
        if (const auto topScreen = mScreensStack.back().get(); topScreen->GetState() == UIScreen::ScreenState::Active) {
            topScreen->ProcessInput(key);
        }
    }
}

void UIManager::UpdateScreens(const float deltaTime) {
    bool screensRemoved = false;

    while (!mScreensStack.empty() && mScreensStack.back()->GetState() == UIScreen::ScreenState::Closing) {
        mScreensStack.pop_back();
        screensRemoved = true;
    }

    if (screensRemoved && !mScreensStack.empty()) {
        mScreensStack.back()->Resume();
    }

    for (const auto& screen : mScreensStack) {
        screen->Update(deltaTime);
    }
}

void UIManager::SendScreensDrawCommands(RenderSubsystem* renderer) const {
    for (const auto& screen : mScreensStack) {
        screen->SendDrawCommands(renderer);
    }
}
