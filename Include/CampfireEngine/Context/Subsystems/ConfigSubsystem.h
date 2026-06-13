#pragma once
#include <string>

struct WindowConfig {
    int width;
    int height;
    std::string title;
};

struct UIConfig {
    std::string UIShaderName;
    std::string UIFontName;
};

class ConfigSubsystem {
public:
    virtual ~ConfigSubsystem() = default;
    [[nodiscard]] virtual const WindowConfig& GetWindowConfig() const = 0;
    [[nodiscard]] virtual const UIConfig& GetUIConfig() const = 0;
};
