#include "CampfireEngine/UI/Elements/UIImage.h"
#include "CampfireEngine/Graphics/Resources/Texture.h"
#include "CampfireEngine/Graphics/Shader/Shader.h"
#include "CampfireEngine/Graphics/Shader/UniformsBlock.h"
#include "../../Graphics/Renderer/RenderUtils.h"
#include "CampfireEngine/Context/Subsystems/RenderSubsystem.h"

UIImage::UIImage(const Vector2 &offset, const float scale, const float angle, const int drawOrder)
:RegularUIElement(offset, Vector2::One, scale, angle, drawOrder)
,mTexture(nullptr)
{}

void UIImage::SetTexture(Texture *texture) {
    if (!texture) {
        return;
    }

    mTexture = texture;
    SetSize(Vector2{texture->GetWidth(), texture->GetHeight()});
}


void UIImage::SendDrawCommand(RenderSubsystem *renderer) {
    const auto shader = GetShader();
    const auto shaderID = shader ? shader->GetID() : 0;
    const auto textureID = mTexture ? mTexture->GetID() : 0;

    const uint64_t key = RenderUtils::GenerateRenderKey(shaderID, 0, textureID, GetDrawOrder());

    UniformsBlock block;
    block.SetMatrix(shader,"uTransform", GetTransform());
    block.SetVector(shader,"uColor", Color::Blue);
    block.SetFloat(shader,"uTextureFactor", 1.0f);
    block.SetVector(shader,"uTextureRect", Vector4(0.0f, 0.0f, 1.0f, 1.0f));

    const RenderUtils::SpriteCommand cmd = {
        key,
        shaderID,
        textureID,
        shader,
        mTexture,
        block
    };

   renderer->PushUICommand(cmd);
}
