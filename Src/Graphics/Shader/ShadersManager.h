#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include "CampfireEngine/Subsystems/ShadersSystem.h"

class Shader;

class ShadersManager : public ShadersSystem{
public:
    ShadersManager();
    ~ShadersManager() override;

    Shader* GetShader(const std::string& name) override;
    void RemoveShader(const std::string& name) override;
    void UnloadShaders() override;

private:
    std::unordered_map<std::string, std::unique_ptr<Shader>> mShaders;
};
