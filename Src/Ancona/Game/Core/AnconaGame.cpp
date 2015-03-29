#include <Ancona/Engine/Core/Game.hpp>
#include <Ancona/Engine/Resource/ResourceLoaderInit.hpp>
#include <Ancona/Engine/Resource/ResourceLibrary.hpp>
#include <Ancona/Engine/Screens/LoadingScreen.hpp>
#include <Ancona/Game/Core/AnconaGame.hpp>
#include <Ancona/Game/Screens/GameScreen.hpp>

using namespace ild;

AnconaGame::AnconaGame(
        int windowWidth, 
        int windowHeight, 
        const std::string & title)
    : Game(windowWidth, windowHeight, title)
{
    ResourceLoaderInit::Init();
    CreateInitialScreen();
}

void AnconaGame::CreateInitialScreen()
{
    _screenManager->Push(
            new GameScreen(*_screenManager, 0));
}
