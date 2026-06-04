#pragma once
#include <SDL2/SDL_video.h>

namespace SDLUtils {
    [[nodiscard]] bool SetupSubSystems();
    void ShutdownSubSystems();

    struct SDLWindowDeleter {
        void operator()(SDL_Window* window) const {
            if (window) {
                SDL_DestroyWindow(window);
            }
        }
    };
}
