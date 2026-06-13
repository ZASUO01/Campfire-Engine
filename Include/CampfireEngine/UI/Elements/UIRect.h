#pragma once
#include "RegularUIElement.h"

class UIRect : public RegularUIElement {
public:
    explicit UIRect(const Vector2 &offset = Vector2::Zero, const Vector2 &size = Vector2{50.0f, 50.0f}, float scale = 1.0f, float angle = 0.0f, int drawOrder = 100);

    void SetColor(const Vector3 &color) { mColor = color; }
private:
    void SendDrawCommand(RenderSubsystem* renderer) override;

    Vector3 mColor;

friend class UIScreen;
};