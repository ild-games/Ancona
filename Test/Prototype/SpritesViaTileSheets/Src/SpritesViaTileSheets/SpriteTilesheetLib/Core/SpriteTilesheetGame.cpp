#include <Ancona/Framework/Resource/ResourceLoaderInit.hpp>

#include "SpriteTilesheetGame.hpp"
#include "../Screens/TestScreen.hpp"

using namespace ild;

SpriteTilesheetGame::SpriteTilesheetGame(
        int width,
        int height,
        PlatformBase * platform) :
    Game(width, height, "Sprites Via TileSheets"),
    _platform(platform)
{
    CreateInitialScreen();
    ResourceLoaderInit::Init();
}

void SpriteTilesheetGame::CreateInitialScreen()
{
    _screenManager->Push(
            new TestScreen(*_screenManager, _platform->inputHandler()));
}
