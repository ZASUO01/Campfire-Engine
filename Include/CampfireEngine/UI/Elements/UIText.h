#pragma once
#include <string>
#include <unordered_map>
#include "RegularUIElement.h"

class Texture;
namespace FontData {
    struct GlyphInfo;
    using GlyphTable = std::unordered_map<char, GlyphInfo>;
}

class UIText : public RegularUIElement {
public:
    explicit UIText(const Vector2& offset = Vector2::Zero, float scale = 1.0f,
        float angle = 0.0f, int drawOrder = 100);

    void SetFont(class Font* font);
    void SetFontSize(int fontSize);
    void SetWrapLength(int wrapLength);
    void SetLineSpacing(float lineSpacing);
    void SetText(const std::string& text);
    void SetColor(const Vector3& color) { mColor = color; }

private:
    Font* mFont;
    const FontData::GlyphTable* mGlyphMapCache;
    Texture* mAtlasTextureCache;

    int mFontSize;
    Vector3 mColor;
    std::string mText;
    int mWrapLength;
    float mLineSpacing;

    void SendDrawCommand(RenderSubsystem* renderer) override;
    [[nodiscard]] const FontData::GlyphInfo* GetCharMapping(char c) const;

friend class UIScreen;
};