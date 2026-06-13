#pragma once
#include <memory>

struct CoreContext;

class UISubsystem  {
public:
    virtual ~UISubsystem() = default;
    virtual void PushScreen(std::unique_ptr<class UIScreen> screen, const CoreContext& ctx) = 0;
};