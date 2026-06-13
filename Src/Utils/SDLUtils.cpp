#include "CampfireEngine/Utils/SDLUtils.h"
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

void SDL_WindowDeleter::operator()(SDL_Window* window) const {
    if (window) {
        SDL_DestroyWindow(window);
    }
}

void SDL_GLContextDeleter::operator()(void* context) const {
    if (context) {
        SDL_GL_DeleteContext(context);
    }
}

void SDL_SurfaceDeleter::operator()(SDL_Surface* surface) const {
    if (surface) {
        SDL_FreeSurface(surface);
    }
}

void TTF_FontDeleter::operator()(TTF_Font *font) const {
    if (font) {
        TTF_CloseFont(font);
    }
}


UniqueSurface SDLUtils::LoadSurfaceFromImage(const std::string &filePath) {
    SDL_Surface* loaded = IMG_Load(filePath.c_str());

    if (!loaded) {
        SDL_Log("[SDL UTILS] Failed to load image %s: %s", filePath.c_str(), IMG_GetError());
        return {nullptr};
    }

    SDL_Surface *surface = SDL_ConvertSurfaceFormat(loaded, SDL_PIXELFORMAT_ABGR8888, 0);
    SDL_FreeSurface(loaded);

    if (!surface) {
        SDL_Log("[SDLUtils] Failed to convert surface format %s: %s", filePath.c_str(), IMG_GetError());
        return {nullptr};
    }

    return UniqueSurface(surface);
}

UniqueTTFFont SDLUtils::LoadTTFFontFromFile(const std::string &filePath, const int size) {
    TTF_Font* font = TTF_OpenFont(filePath.c_str(), size);

    if (!font) {
        SDL_Log("[SDL UTILS] Failed to load font %s: %s", filePath.c_str(), TTF_GetError());
        return {nullptr};
    }

    return UniqueTTFFont(font);
}
