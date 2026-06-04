#pragma once
#include <string>
#include <unordered_map>
#include "Math/Math.h"

class Shader {
public:
    Shader();
    ~Shader();

    [[nodiscard]] bool Build(const std::string& vertexShaderString, const std::string& fragmentShaderString);
    void SetActive() const;

    // Prevent copies
    Shader& operator=(const Shader&) = delete;
    Shader(const Shader&) = delete;

    // Getters
    int GetUniformLocation(const std::string& name) const;
    unsigned int GetID() const { return mShaderProgram; }

    static void SetVectorUniform (int location, const Vector2& vector);
    static void SetVectorUniform (int location, const Vector3& vector);
    static void SetVectorUniform (int location, const Vector4& vector);
    static void SetMatrixUniform(int location, const Matrix4& matrix);
    static void SetFloatUniform(int location, float value);
    static void SetTextureUniform(int location, int value);
private:
    struct UniformInfo {
        int location;
        unsigned int type;
    };

    void Destroy();
    void IntrospectUniforms();

    static bool CompileShader(const std::string& shaderString, unsigned int shaderType, unsigned int& outShaderID);
    static bool IsCompiled(unsigned int shader);
    bool IsValidProgram() const;

    unsigned int mShaderProgram;

    std::pmr::unordered_map<std::string, UniformInfo> mUniforms;
};