#include <Ancona/Framework/Resource/ResourceLoaderInit.hpp>

#include "RotationGame.hpp"
#include "../Screens/TestScreen.hpp"

using namespace ild;

RotationGame::RotationGame(
        int width,
        int height,
        RotationPlatformFactory * platform) :
    Game(width, height, "Rotation Test"),
    _platform(platform)
{
    CreateInitialScreen();
    ResourceLoaderInit::Init();
}

void RotationGame::CreateInitialScreen()
{
    _screenManager->Push(
            new TestScreen(*_screenManager, _platform->inputHandler()));
}
