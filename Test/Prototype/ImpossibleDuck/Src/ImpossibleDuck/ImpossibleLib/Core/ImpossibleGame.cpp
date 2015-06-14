#include "ImpossibleGame.hpp"
#include "../Screens/ImpossibleScreen.hpp"
#include <Ancona/Framework/Resource/ResourceLoaderInit.hpp>
#include <Ancona/Framework/Resource/ResourceLibrary.hpp>
#include <Ancona/Framework/Resource/RequestList.hpp>
#include <Ancona/Framework/Screens/LoadingScreen.hpp>
#include <Ancona/Util/Data.hpp>

using namespace ild;

ImpossibleGame::ImpossibleGame(
        int width,
        int height,
        PlatformBase * platform) :
    Game(width,height,"Impossible Duck"),
    _platform(platform)
{
    CreateInitialScreen();
    ResourceLoaderInit::Init();
}

void ImpossibleGame::CreateInitialScreen()
{
    _screenManager->Push(
            new ImpossibleScreen(*_screenManager, _platform->inputHandler()));
}
