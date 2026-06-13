#pragma once
#include "Subsystems/AssetsSubsystem.h"
#include "Subsystems/ConfigSubsystem.h"
#include "Subsystems/ShadersSubsystem.h"

struct CoreContext {
    ConfigSubsystem* configCtx;
    AssetsSubsystem* assetsCtx;
    ShadersSubsystem* shaderCtx;
};
