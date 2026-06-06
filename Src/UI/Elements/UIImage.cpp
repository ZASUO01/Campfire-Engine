#include "CampfireEngine/UI/Elements/UIImage.h"
#include "CampfireEngine/Subsystems/AssetsSystem.h"
#include "CampfireEngine/Graphics/Resources/Texture.h"
#include "CampfireEngine/Graphics/Shader/UniformsBlock.h"
#include "Graphics/Renderer/RendererUtils.h"

UIImage::UIImage(const Vector2 &offset, const float scale, const float angle, const int drawOrder)
:UIElement(offset, Vector2::One, scale, angle, drawOrder)
,mTexture(nullptr)
{}

void UIImage::SetTexture(const std::string& name, AssetsSystem* assets) {
    if (const auto texture = assets->GetTexture(name)) {
        mTexture = texture;

        SetSize(Vector2(static_cast<float>(texture->GetWidth()), static_cast<float>(texture->GetHeight())));
    }
}

void UIImage::SendDrawCommand(RendererSystem* renderer) {

}