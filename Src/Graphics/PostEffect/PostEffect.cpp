#include "CampfireEngine/Graphics/PostEffect/PostEffect.h"
#include "CampfireEngine/Graphics/Shader/UniformsBlock.h"
#include <utility>
#include <SDL2/SDL_timer.h>
#include "CampfireEngine/Subsystems/RendererSystem.h"
#include "Graphics/Renderer/RendererUtils.h"

PostEffect::PostEffect(Shader* shader, std::string  name)
:mName(std::move(name)) {
    if (shader) {
        mShader = shader;
    }

    mUniformsBlock = std::make_unique<UniformsBlock>();
}

PostEffect::~PostEffect() = default;

void PostEffect::Update(const float deltaTime, RendererSystem* renderer) {
    const uint32_t totalTicks = SDL_GetTicks();

    UpdateUniforms(deltaTime, totalTicks);

    SendRenderCommand(renderer);
}

void PostEffect::SendRenderCommand(RendererSystem* renderer) const {
    if (!mShader) {
        return;
    }

    RendererUtils::PostEffectCommand cmd{};
    cmd.shader = mShader;
    cmd.block = mUniformsBlock.get();

    renderer->SetPostEffectCommand(cmd);
}

