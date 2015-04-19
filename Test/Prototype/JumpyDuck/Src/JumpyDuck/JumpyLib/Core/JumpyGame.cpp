#include "JumpyGame.hpp"
#include "../Screens/JumpyScreen.hpp"
#include <Ancona/Framework/Resource/ResourceLoaderInit.hpp>
#include <Ancona/Framework/Resource/ResourceLibrary.hpp>
#include <Ancona/Framework/Resource/RequestList.hpp>
#include <Ancona/Framework/Screens/LoadingScreen.hpp>

using namespace ild;

JumpyGame::JumpyGame(int width, int height) : Game(width,height,"Jumpy Duck")
{
    CreateInitialScreen();
    ResourceLoaderInit::Init();
}

void JumpyGame::CreateInitialScreen()
{
    _screenManager->Push(new JumpyScreen(*_screenManager));
}
