#pragma once
#include <memory>

class PostEffect {
public:
    explicit PostEffect(class Shader *shader, std::string  name);
    virtual ~PostEffect();

    [[nodiscard]] Shader* GetShader() const { return mShader; }
    void Update(float deltaTime, class RendererSystem *renderer);

    [[nodiscard]] const std::string& GetName() const { return mName; }
protected:
    virtual void UpdateUniforms(float deltaTime, uint32_t totalTicks) = 0;
    void SendRenderCommand(RendererSystem *renderer) const;

    Shader* mShader;
    std::unique_ptr<class UniformsBlock> mUniformsBlock;

private:
    std::string mName;
};
