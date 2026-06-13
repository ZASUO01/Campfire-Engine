#pragma once
#include "CampfireEngine/Graphics/Resources/Texture.h"
#include "CampfireEngine/Graphics/Shader/Shader.h"
#include "CampfireEngine/Graphics/Shader/UniformsBlock.h"

namespace  RenderUtils {
    struct SpriteCommand {
        uint64_t key;
        uint32_t shaderID;
        uint32_t textureID;

        Shader* shader;
        Texture* texture;
        UniformsBlock block;

        bool operator<(const SpriteCommand &other) const {
            return key < other.key;
        }
    };

    inline uint64_t GenerateRenderKey(const uint32_t shaderID, const uint32_t vaID, const uint32_t textureID, const uint32_t specialOrder = 0) {
        uint64_t renderKey = 0;

        renderKey |= static_cast<unsigned long int>(shaderID & 0xFFFF) << 48;
        renderKey |= static_cast<unsigned long int>(vaID & 0xFFFF) << 32;
        renderKey |= static_cast<unsigned long int>(textureID & 0xFFFF) << 16;
        renderKey |= static_cast<unsigned long int>(specialOrder & 0xFFFF);

        return renderKey;
    }
}
