#include "Core/GameData.h"

GameData::GameData()
:mMainConfig({}) {
    ApplyDefaultConfig();
}

GameData::~GameData() = default;

void GameData::ApplyDefaultConfig() {
    mMainConfig.WINDOW_WIDTH = DEFAULT_WINDOW_WIDTH;
    mMainConfig.WINDOW_HEIGHT = DEFAULT_WINDOW_HEIGHT;
    mMainConfig.WINDOW_TITLE = DEFAULT_WINDOW_TITLE;
}
