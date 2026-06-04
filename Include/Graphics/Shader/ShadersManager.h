#pragma once
#include <memory>
#include <string>
#include <unordered_map>

class ShadersManager {
public:
    ~ShadersManager();

    class Shader* GetShader(const std::string& name);
    void RemoveShader(const std::string& name);
    void UnloadShaders();

private:
    std::unordered_map<std::string, std::unique_ptr<Shader>> mShaders;
};