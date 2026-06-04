#pragma once
#include <string>

class Shader;
class GameBase;

namespace ObjectFactories {
    Shader* BuildShader(const GameBase* game, const std::string& name);
}