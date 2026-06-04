#pragma once
#include <memory>

class PostEffect {
public:
    explicit PostEffect(class Shader *shader, const std::string& name);
    virtual ~PostEffect();

    [[nodiscard]] Shader* GetShader() const { return mShader; }
    void ApplyUniforms();

    [[nodiscard]] const std::string& GetName() const { return mName; }
protected:
    virtual void SetupUniforms() = 0;

    Shader* mShader;
    std::unique_ptr<class UniformsBlock> mUniformsBlock;

private:
    std::string mName;
};
