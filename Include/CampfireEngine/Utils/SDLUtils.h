#pragma once
#include "CampfireEngine/Types/SDLTypesFwd.h"

namespace SDLUtils{
    UniqueSurface LoadSurfaceFromImage(const std::string& filePath);
    UniqueTTFFont LoadTTFFontFromFile(const std::string &filePath, int size);
}