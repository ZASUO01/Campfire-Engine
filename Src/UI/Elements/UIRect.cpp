#include  "CampfireEngine/UI/Elements/UIRect.h"
#include "CampfireEngine/Graphics/Shader/Shader.h"
#include "CampfireEngine/Graphics/Shader/UniformsBlock.h"
#include  "../../Graphics/Renderer/RenderUtils.h"
#include "CampfireEngine/Context/Subsystems/RenderSubsystem.h"

UIRect::UIRect(const Vector2 &offset, const Vector2 &size, const float scale, const float angle, const int drawOrder)
:RegularUIElement(offset, size, scale, angle, drawOrder)
,mColor(Color::Blue)
{}

void UIRect::SendDrawCommand(RenderSubsystem* renderer) {
    const auto shader = GetShader();
    const auto shaderID = shader ? shader->GetID() : 0;

    const uint64_t key = RenderUtils::GenerateRenderKey(shaderID, 0, 0, GetDrawOrder());

    UniformsBlock block;
    block.SetMatrix(shader,"uTransform", GetTransform());
    block.SetVector(shader,"uColor", mColor);
    block.SetFloat(shader,"uTextureFactor", 0.0f);
    block.SetVector(shader,"uTextureRect", Vector4(0.0f, 0.0f, 1.0f, 1.0f));

    const RenderUtils::SpriteCommand cmd = {
        key,
        shaderID,
        0,
        shader,
        nullptr,
        block
    };

    renderer->PushUICommand(cmd);
}