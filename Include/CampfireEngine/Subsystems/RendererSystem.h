#pragma once

namespace RendererUtils {
    struct PostEffectCommand;
}

class RendererSystem {
public:
    virtual ~RendererSystem() = default;
    virtual void SetPostEffectCommand(const RendererUtils::PostEffectCommand& cmd) = 0;
};