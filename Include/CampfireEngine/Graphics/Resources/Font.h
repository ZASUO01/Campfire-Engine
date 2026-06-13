#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include "CampfireEngine/Types/SDLTypesFwd.h"

class Texture;
namespace FontData {
    struct GlyphInfo {
        float uMin, vMin;
        float uMax, vMax;

        int width, height;
        int bearingX, bearingY;
        int advance;
    };

    using GlyphTable = std::unordered_map<char, GlyphInfo>;
};

class Font {
public:
    Font();
    ~Font();

    Font(const Font&) = delete;
    Font& operator=(const Font&) = delete;

    // Load from a file
    bool Load(const std::string& fileName);


    const FontData::GlyphTable* GetGlyphTable(int fontSize) const;
    Texture* GetAtlasTexture(int fontSize) const;

private:
    static constexpr int ATLAS_WIDTH = 512;
    static constexpr int ATLAS_HEIGHT = 512;

    std::unordered_map<int , std::unique_ptr<Texture>> mAtlasTexturesMap;
    std::unordered_map<int, std::unordered_map<char, FontData::GlyphInfo>> mGlyphsMap;

    void GenerateAtlas(TTF_Font* font, int size);
};
