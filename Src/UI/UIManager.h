#pragma once
#include <memory>
#include <vector>
#include "CampfireEngine/Context/CoreContext.h"
#include "CampfireEngine/Context/Subsystems/UISubsystem.h"

class UIManager : public UISubsystem {
public:
    UIManager();
    ~UIManager() override;

    static bool Load(const CoreContext& ctx) ;

    void PushScreen(std::unique_ptr<UIScreen> screen, const CoreContext& ctx) override;
    void ProcessTopScreenInput(int key) const;
    void UpdateScreens(float deltaTime);
    void SendScreensDrawCommands(class RenderSubsystem* renderer) const;

private:
    std::vector<std::unique_ptr<UIScreen>> mScreensStack;
};
