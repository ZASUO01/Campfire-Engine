#include "Drawer.h"
#include "glad/glad.h"
#include "Graphics/Geometry/VertexArray.h"
#include "CampfireEngine/Graphics/PostEffect/PostEffect.h"
#include "CampfireEngine/Graphics/Resources/Texture.h"
#include "CampfireEngine/Graphics/Shader/Shader.h"

Drawer::Drawer(){
    GenerateFullQuadVertices();
}

Drawer::~Drawer() = default;

void Drawer::DrawPostPass(PostEffect *effect, const Texture* texture) const {
    if (!mFullQuadVertices) {
        return;
    }

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    const auto shader = effect->GetShader();
    shader->SetActive();
    effect->ApplyUniforms();

    if (texture) {
        texture->SetActive();
    }

    mFullQuadVertices->SetActive();
    const unsigned int numIndices = mFullQuadVertices->GetNumIndices();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(numIndices), GL_UNSIGNED_INT, nullptr);
}

void Drawer::GenerateFullQuadVertices() {
    constexpr float vertices[] = {
        -1.0f,  1.0f,       0.0f, 1.0f,
        -1.0f, -1.0f,       0.0f, 0.0f,
         1.0f, -1.0f,       1.0f, 0.0f,
         1.0f,  1.0f,       1.0f, 1.0f
    };

    const unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    constexpr unsigned int stride = 4 * sizeof(float); // 4 x 4 bytes;
    std::vector<VertexArray::VertexAttribute> layout;

    layout.emplace_back(0, 2, GL_FLOAT, GL_FALSE, 0);
    layout.emplace_back(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float));

    mFullQuadVertices = std::make_unique<VertexArray>(vertices, 4, indices, 6, stride, layout);
}