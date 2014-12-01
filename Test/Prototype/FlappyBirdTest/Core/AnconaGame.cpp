#include <Ancona/Engine/Core/Game.hpp>
#include <Ancona/Engine/Resource/ResourceLoaderInit.hpp>
#include <Ancona/Engine/Resource/ResourceLibrary.hpp>
#include <Ancona/Engine/Screen/LoadingScreen.hpp>
#include <Ancona/Game/Core/AnconaGame.hpp>

#include "../Screen/TestScreen.hpp"
#include <iostream>

using namespace ild;

AnconaGame::AnconaGame(
        int windowWidth, 
        int windowHeight, 
        const std::string & title)
    : Game(windowWidth, windowHeight, title)
{
    sf::View view = _window.getView();
    view.zoom(.5f);
    _window.setView(view);
    ResourceLoaderInit::Init();
    CreateInitialScreen();
}

AnconaGame::~AnconaGame()
{
    ResourceLibrary::Return(*_requestList);
    delete _requestList;
}

void AnconaGame::CreateInitialScreen()
{
    _requestList = new RequestList("TestRequestList.txt");
    _screenManager->Push(
            new TestScreen(*_screenManager));
    _screenManager->Push(
            new LoadingScreen(*_screenManager, *_requestList));
}
