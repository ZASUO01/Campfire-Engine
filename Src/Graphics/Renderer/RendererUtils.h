#pragma once
#include "CampfireEngine/Graphics/Shader/UniformsBlock.h"
#include "CampfireEngine/Graphics/Shader/Shader.h"

namespace RendererUtils {
    struct PostEffectCommand {
        UniformsBlock* block;
        Shader* shader;
    };
}
