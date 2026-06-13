#pragma once
#include <memory>
#include <unordered_map>
#include "CampfireEngine/Context/Subsystems/ShadersSubsystem.h"

class ShadersManager: public ShadersSubsystem{
public:
    ~ShadersManager() override;

    Shader* GetShader(const std::string& name) override;
    void RemoveShader(const std::string& name) override;
    void UnloadShaders();
private:
    std::unordered_map<std::string, std::unique_ptr<Shader>> mShaders;
};
