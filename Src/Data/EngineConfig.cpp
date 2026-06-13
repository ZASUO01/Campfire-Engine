#include "CampfireEngine/Data/EngineConfig.h"

EngineConfig::EngineConfig() {
    SetDefaultConfig();
}

EngineConfig::~EngineConfig() = default;

void EngineConfig::SetDefaultConfig() {
    mWindowConfig.width = DEFAULT_WINDOW_WIDTH;
    mWindowConfig.height = DEFAULT_WINDOW_HEIGHT;
    mWindowConfig.title = DEFAULT_WINDOW_TITLE;

    mUIConfig.UIShaderName = DEFAULT_UI_SHADER_NAME;
    mUIConfig.UIFontName = DEFAULT_UI_FONT_NAME;
}
