#pragma once
#include <memory>

#include "RendererUtils.h"

class Drawer {
public:
    Drawer();
    ~Drawer();

    void DrawPostPass(const RendererUtils::PostEffectCommand &cmd, const class Texture* texture) const;

private:
    void GenerateFullQuadVertices();

    std::unique_ptr<class VertexArray> mFullQuadVertices;
};
