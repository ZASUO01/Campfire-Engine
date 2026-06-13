#pragma once

namespace RenderUtils {
    struct SpriteCommand;
}

class RenderSubsystem {
public:
    virtual ~RenderSubsystem() = default;
    virtual void PushUICommand(const RenderUtils::SpriteCommand &command) = 0;
};
