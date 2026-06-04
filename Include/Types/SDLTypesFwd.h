#pragma once
#include <memory>

struct SDL_Window;
struct SDLWindowDeleter {
    void operator()(SDL_Window* window) const;
};

using UniqueSDLWindow = std::unique_ptr<SDL_Window, SDLWindowDeleter>;

struct SDL_GLContextDeleter {
    using pointer = void*;
    void operator()(void* context) const;
};

using UniqueGLContext = std::unique_ptr<void, SDL_GLContextDeleter>;