#pragma once

class RendererSystem {
public:
    virtual ~RendererSystem() = default;
    virtual void Draw() = 0;
};