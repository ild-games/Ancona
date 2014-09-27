#include <Ancona/Engine/Core/Game.hpp>
#include <Ancona/Game/Core/AnconaGame.hpp>
#include <Ancona/Game/Screen/TestScreen.hpp>

using namespace ild;

AnconaGame::AnconaGame(int windowWidth, int windowHeight, const std::string & title)
    : Game(windowWidth, windowHeight, title)
{
    CreateInitialScreen();
}

void AnconaGame::CreateInitialScreen()
{
    _screenManager->Push(new TestScreen(*_screenManager));
}
