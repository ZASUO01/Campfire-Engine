#pragma once
#include <memory>
#include <vector>
#include "RenderUtils.h"

class Drawer {
public:
    Drawer();
    ~Drawer();

    void DrawUIPass(std::vector<RenderUtils::SpriteCommand>& UICommands, const Matrix4& ortho) const;
private:
    void GenerateSpriteVertices();

    std::unique_ptr<class VertexArray> mSpriteVertices;
};
