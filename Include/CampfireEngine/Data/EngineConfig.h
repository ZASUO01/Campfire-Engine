#pragma once
#include <string_view>
#include "CampfireEngine/Context/Subsystems/ConfigSubsystem.h"

class EngineConfig : public ConfigSubsystem {
public:
    EngineConfig();
    ~EngineConfig() override;

    [[nodiscard]] const WindowConfig& GetWindowConfig() const override { return mWindowConfig; }
    [[nodiscard]] const UIConfig& GetUIConfig() const override { return mUIConfig; }
private:
    void SetDefaultConfig();

    WindowConfig mWindowConfig;
    UIConfig mUIConfig;

    // Constants
    static constexpr int DEFAULT_WINDOW_WIDTH = 1024;
    static constexpr int DEFAULT_WINDOW_HEIGHT = 768;
    static constexpr std::string_view DEFAULT_WINDOW_TITLE = "Campfire Engine";

    static constexpr std::string_view DEFAULT_UI_SHADER_NAME = "../CampfireEngine/Shaders/Sprites";
    static constexpr std::string_view DEFAULT_UI_FONT_NAME = "../CampfireEngine/Assets/Fonts/JetBrainsMono.ttf";
};
