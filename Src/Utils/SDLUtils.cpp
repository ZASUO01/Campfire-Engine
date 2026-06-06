#include "SDLUtils.h"
#include <SDL2/SDL_log.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

bool SDLUtils::SetupSubSystems() {
    // Init Video
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS |  SDL_INIT_AUDIO) != 0) {
        SDL_Log("[SDL UTILS] Unable to initialize SDL Video: %s", SDL_GetError());
        return false;
    }

    // Init image
    if (constexpr int imgFlags = IMG_INIT_PNG; !(IMG_Init(imgFlags) & imgFlags))
    {
        SDL_Log("[SDL UTILS] Unable to initialize SDL_image: %s", IMG_GetError());
        return false;
    }

    // Init font
    if (TTF_Init() != 0){
        SDL_Log("[SDL UTILS] Failed to initialize SDL_ttf");
        return false;
    }

    // Set OpenGL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Enable double buffering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // Force OpenGL to use hardware acceleration
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    return true;
}

void SDLUtils::ShutdownSubSystems() {
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
