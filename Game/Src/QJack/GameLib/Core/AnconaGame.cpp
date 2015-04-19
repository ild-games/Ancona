#include <Ancona/Core2D/Core/Game.hpp>
#include <Ancona/Framework/Resource/ResourceLoaderInit.hpp>
#include <Ancona/Framework/Resource/ResourceLibrary.hpp>
#include <Ancona/Framework/Screens/LoadingScreen.hpp>
#include <QJack/GameLib/Core/AnconaGame.hpp>
#include <QJack/GameLib/Screens/GameScreen.hpp>

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
