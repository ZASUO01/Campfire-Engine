#pragma once
#include <memory>

struct SDL_Window;
struct SDL_WindowDeleter {
    void operator()(SDL_Window* window) const;
};

using UniqueSDLWindow = std::unique_ptr<SDL_Window, SDL_WindowDeleter>;

struct SDL_GLContextDeleter {
    void operator()(void* context) const;
};

using UniqueGLContext = std::unique_ptr<void, SDL_GLContextDeleter>;

struct  SDL_Surface;
struct SDL_SurfaceDeleter {
    void operator()(SDL_Surface* surface) const;
};

using UniqueSurface = std::unique_ptr<SDL_Surface, SDL_SurfaceDeleter>;

struct TTF_Font;
struct TTF_FontDeleter {
    void operator()(TTF_Font* font) const;
};

using UniqueTTFFont = std::unique_ptr<TTF_Font, TTF_FontDeleter>;