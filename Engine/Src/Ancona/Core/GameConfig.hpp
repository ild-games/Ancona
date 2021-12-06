#pragma once

#include <Ancona/HAL.hpp>

namespace ild
{

struct GameConfig
{
    int windowWidth = 1280;
    int windowHeight = 720;
    std::string title = "Ancona Game";
    bool isVSyncEnabled = true;
    bool isFpsLimited = true;
    float fpsLimit = 60.0f;
    float fixedUpdateFps = 60.0f;
    float minFps = 45.0f;
    bool isKeyRepeatEnabled = false;
    unsigned int style = ildhal::WindowStyle::Default;
};
} // namespace ild
