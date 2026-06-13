#include "Drawer.h"
#include <algorithm>
#include "Graphics/Geometry/VertexArray.h"
#include <glad/glad.h>

Drawer::Drawer(){
    GenerateSpriteVertices();
}

Drawer::~Drawer() = default;

void Drawer::DrawUIPass(std::vector<RenderUtils::SpriteCommand>& UICommands, const Matrix4& ortho) const {
    if (UICommands.empty()) {
        return;
    }

    std::ranges::sort(UICommands, [](const auto& a, const auto& b) {
        return a.key < b.key;
    });

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    uint32_t lastShaderID = 0;
    const Shader* shader = nullptr;

    mSpriteVertices->SetActive();
    const auto numIndices = mSpriteVertices->GetNumIndices();

    uint32_t lastTextureID = 0;
    const Texture* texture = nullptr;

    for (auto& cmd: UICommands) {
        // The shader must be specified in this command
        if (!cmd.shader) {
            continue;
        }

        // Activate shader if different from the previous one
        if (cmd.shaderID != lastShaderID) {
            shader = cmd.shader;
            shader->SetActive();

            if (const int texLocation = shader->GetUniformLocation("uTexture"); texLocation >= 0) {
                Shader::SetTextureUniform(texLocation, 0);
            }

            // set the view projection matrix if it exists in the shader
            if (const int viewProjUniformLocation = shader->GetUniformLocation("uViewProjection"); viewProjUniformLocation >= 0) {
                Shader::SetMatrixUniform(viewProjUniformLocation, ortho);
            }

            lastShaderID = cmd.shaderID;
            lastTextureID = 0;
        }

        // Activate texture if different from previous one
        if (cmd.textureID != lastTextureID) {
            texture = cmd.texture;

            // active the texture if it exists
            if (texture && cmd.textureID != 0) {
                texture->SetActive();
            }
            // deactivate the previous one otherwise
            else {
                glBindTexture(GL_TEXTURE_2D, 0);
            }

            lastTextureID = cmd.textureID;
        }

        cmd.block.ApplyUniforms();
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(numIndices), GL_UNSIGNED_INT, nullptr);
    }

    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    UICommands.clear();
}

void Drawer::GenerateSpriteVertices() {
    constexpr float vertices[] = {
        -0.5f,  0.5f, 0.0f, 1.0f,
         -0.5f, -0.5f, 0.0f, 0.0f,
          0.5f, -0.5f, 1.0f, 0.0f,
          0.5f,  0.5f, 1.0f, 1.0f
        };

    const unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0,
    };

    constexpr unsigned int stride = 4 * sizeof(float); // 4 x 4 bytes;

    std::vector<VertexArray::VertexAttribute> layout;
    layout.emplace_back(0, 2, GL_FLOAT, false, 0);
    layout.emplace_back(1, 2, GL_FLOAT, false, 2 * sizeof(float));

    mSpriteVertices = std::make_unique<VertexArray>(vertices, 4, indices, 6, stride, layout);
}