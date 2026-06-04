#include "Graphics/PostEffect/PostEffect.h"
#include "Graphics/Shader/UniformsBlock.h"

PostEffect::PostEffect(Shader* shader, const std::string& name)
:mName(name) {
    if (shader) {
        mShader = shader;
    }

    mUniformsBlock = std::make_unique<UniformsBlock>();
}

PostEffect::~PostEffect() = default;

void PostEffect::ApplyUniforms() {
    SetupUniforms();
    mUniformsBlock->ApplyUniforms();
}
