#pragma once
#include <string>
#include "UIElement.h"
#include "CampfireEngine/Math/Math.h"

class UIImage :public UIElement {
public:
    explicit UIImage(const Vector2& offset = Vector2::Zero, float scale = 1.0f, float angle = 0.0f, int drawOrder = 100);

    void SetTexture(const std::string& name, class AssetsSystem* assets);
    void SendDrawCommand(RendererSystem* renderer) override;

private:
    class Texture* mTexture;
};