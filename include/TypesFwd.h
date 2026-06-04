#pragma once
#include <memory>

// SDL Types
struct SDL_Window;
struct SDLWindowDeleter {
    void operator()(SDL_Window* window) const;
};

using UniqueSDLWindow = std::unique_ptr<SDL_Window, SDLWindowDeleter>;