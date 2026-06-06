#pragma once
#include "CampfireEngine/Graphics/Shader/UniformsBlock.h"
#include "CampfireEngine/Graphics/Shader/Shader.h"
#include "CampfireEngine/Graphics/Resources/Texture.h"

namespace RendererUtils {
    struct SpriteCommand {
        uint64_t key;
        uint32_t shaderID;
        uint32_t textureID;

        Shader* shader;
        Texture* texture;
        UniformsBlock uniformsBlock;

        bool operator<(const SpriteCommand &other) const {
            return key < other.key;
        }
    };

    struct PostEffectCommand {
        UniformsBlock* block;
        Shader* shader;
    };

    inline uint64_t GenerateRenderKey(const uint32_t shaderID, const uint32_t vaID, const uint32_t textureID, const uint32_t specialOrder = 0) {
        uint64_t renderKey = 0;

        renderKey |= static_cast<unsigned long int>(specialOrder & 0xFFFF) << 48;
        renderKey |= static_cast<unsigned long int>(shaderID & 0xFFFF) << 32;
        renderKey |= static_cast<unsigned long int>(vaID & 0xFFFF) << 16;
        renderKey |= static_cast<unsigned long int>(textureID & 0xFFFF);

        return renderKey;
    }
}
