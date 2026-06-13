#pragma once
#include "UIElement.h"

class RegularUIElement : public UIElement {
public:
    explicit RegularUIElement(const Vector2 &offset = Vector2::Zero,
        const Vector2 &size = Vector2::One, float scale = 1.0f, float angle = 0.0f, int drawOrder = 100);

    void Initialize(const struct CoreContext& ctx);
};
