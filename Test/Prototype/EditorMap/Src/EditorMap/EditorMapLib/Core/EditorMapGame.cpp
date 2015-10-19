#include <Ancona/Framework/Resource/ResourceLoaderInit.hpp>

#include "EditorMapGame.hpp"
#include "../Screens/TestScreen.hpp"

using namespace ild;

EditorMapGame::EditorMapGame(
        int width,
        int height,
        EditorMapPlatformFactory * platform) :
    Game(width, height, "Editor Map"),
    _platform(platform)
{
    CreateInitialScreen();
    ResourceLoaderInit::Init();
}

void EditorMapGame::CreateInitialScreen()
{
    _screenManager->Push(
            new TestScreen(*_screenManager, _platform->inputHandler()));
}
