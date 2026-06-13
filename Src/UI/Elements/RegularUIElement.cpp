#include "CampfireEngine/UI/Elements/RegularUIElement.h"
#include "CampfireEngine/Context/CoreContext.h"

RegularUIElement::RegularUIElement(const Vector2 &offset, const Vector2 &size, const float scale, const float angle, const int drawOrder)
:UIElement(offset, size, scale, angle, drawOrder)
{}

void RegularUIElement::Initialize(const CoreContext& ctx) {
    const auto shaderName = ctx.configCtx->GetUIConfig().UIShaderName;
    if (const auto shader = ctx.shaderCtx->GetShader(shaderName)) {
        SetShader(shader);
    }
}
