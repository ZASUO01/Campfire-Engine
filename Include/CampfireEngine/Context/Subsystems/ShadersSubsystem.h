#pragma once
#include <string>

class ShadersSubsystem {
public:
    virtual ~ShadersSubsystem() = default;
    virtual class Shader* GetShader(const std::string& name) = 0;
    virtual void RemoveShader(const std::string& name) = 0;
};