#include "CampfireEngine/Factories/ObjectFactories.h"
#include "CampfireEngine/GameBase.h"
#include "CampfireEngine/Graphics/Shader/Shader.h"
#include "Utils/FileUtils.h"
#include "Graphics/Shader/ShadersManager.h"

Shader *ObjectFactories::BuildShader(const GameBase *game, const std::string &name) {
    std::string vertShaderString;

    if (!FileUtils::LoadFileToString(name+".vert", vertShaderString)) {
        return nullptr;
    }

    std::string fragShaderString;
    if (!FileUtils::LoadFileToString(name+".frag", fragShaderString)) {
        return nullptr;
    }

    const auto shader = game->GetShadersSystem().GetShader(name);
    if (!shader) {
        return nullptr;
    }

    if (!shader->Build(vertShaderString, fragShaderString)) {
        game->GetShadersSystem().RemoveShader(name);
        return nullptr;
    }

    return shader;
}
