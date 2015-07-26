#include <Ancona/Framework/Resource/ResourceLoaderInit.hpp>

#include "GhostedGame.hpp"
#include "../Screens/TestScreen.hpp"

using namespace ild;

GhostedGame::GhostedGame(
        int width,
        int height,
        GhostedPlatformFactory * platform) :
    Game(width, height, "Ghosted"),
    _platform(platform)
{
    CreateInitialScreen();
    ResourceLoaderInit::Init();
}

void GhostedGame::CreateInitialScreen()
{
    _screenManager->Push(
            new TestScreen(*_screenManager, _platform->inputHandler()));
}
