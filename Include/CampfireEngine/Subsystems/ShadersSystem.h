#pragma once
#include <string>

class ShadersSystem {
public:
    virtual ~ShadersSystem() = default;

    virtual class Shader* GetShader(const std::string& name) = 0;
    virtual void RemoveShader(const std::string& name) = 0;
    virtual void UnloadShaders() = 0;
};