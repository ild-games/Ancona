#include "JumpyGame.hpp"
#include "../Screens/JumpyScreen.hpp"
#include <Ancona/Engine/Resource/ResourceLoaderInit.hpp>
#include <Ancona/Engine/Resource/ResourceLibrary.hpp>
#include <Ancona/Engine/Resource/RequestList.hpp>
#include <Ancona/Engine/Screens/LoadingScreen.hpp>

using namespace ild;

JumpyGame::JumpyGame(int width, int height) : Game(width,height,"Jumpy Duck")
{
    CreateInitialScreen();
    ResourceLoaderInit::Init();
}

void JumpyGame::CreateInitialScreen()
{
    RequestList * list = new RequestList();
    list->Add("TexturePNG", "flappy");
    list->Start();
    _screenManager->Push(new JumpyScreen(*_screenManager));
}
