#pragma once
#include <memory>

class Drawer {
public:
    Drawer();
    ~Drawer();

    void DrawPostPass(class PostEffect *effect, const class Texture *texture) const;

private:
    void GenerateFullQuadVertices();

    std::unique_ptr<class VertexArray> mFullQuadVertices;
};
