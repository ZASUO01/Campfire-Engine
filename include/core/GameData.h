#pragma once
#include <string>

class GameData {
public:
    GameData();
    ~GameData();

    struct MainConfig {
        int WINDOW_WIDTH;
        int WINDOW_HEIGHT;
        std::string WINDOW_TITLE;
    };


    [[nodiscard]] const MainConfig& GetMainConfig() const { return mMainConfig; }

private:
    void ApplyDefaultConfig();

    MainConfig mMainConfig;

    // Constants
    static constexpr int DEFAULT_WINDOW_WIDTH = 1024;
    static constexpr int DEFAULT_WINDOW_HEIGHT = 768;
    static constexpr std::string DEFAULT_WINDOW_TITLE = "MY GAME";
};
