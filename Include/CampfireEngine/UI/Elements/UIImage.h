#pragma once
#include "RegularUIElement.h"

class UIImage : public RegularUIElement {
public:
    explicit UIImage(const Vector2& offset = Vector2::Zero, float scale = 1.0f,
        float angle = 0.0f, int drawOrder = 100);

    void SetTexture(class Texture* texture);

private:
    Texture* mTexture;
    void SendDrawCommand(RenderSubsystem* renderer) override;

friend class UIScreen;
};
