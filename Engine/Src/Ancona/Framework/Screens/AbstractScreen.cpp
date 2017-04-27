#include <fstream>
#include <iostream>

#include <json/json.h>

#include <Ancona/Framework/Screens/AbstractScreen.hpp>

using namespace ild;

AbstractScreen::AbstractScreen(
        std::string key,
        ScreenManager & screenManager) :
    __Initialized(false),
    __Entering(false),
    __Exiting(false),
    _screenManager(screenManager),
    KEY(key),
    _transitionColor(0, 0, 0, 255),
    _transitionRect(sf::Vector2f(_screenManager.Window.getSize().x, _screenManager.Window.getSize().y)),
    _defaultCam(sf::View(_screenManager.Window.getDefaultView())) 
{
}

AbstractScreen::~AbstractScreen()
{
    if (_requestList != nullptr && _clearResourcesOnExit)
    {
        ResourceLibrary::Return(*_requestList.get());
    }
}

void AbstractScreen::Entering(float delta)
{
    int alpha = _transitionColor.a;
    alpha -= (TRANSITION_SPEED * delta);
    if (alpha < 0) 
    {
        alpha = 0;
        __Entering = false; 
    }
    _transitionColor.a = (sf::Uint8) alpha;
    _transitionRect.setFillColor(_transitionColor);
    _screenManager.Window.setView(_defaultCam);
    _screenManager.Window.draw(_transitionRect);
}

void AbstractScreen::Exiting(float delta)
{
    int alpha = _transitionColor.a;
    alpha += (TRANSITION_SPEED * delta);
    if (alpha > 255) 
    {
        alpha = 255;
        __Exiting = false; 
    }
    _transitionColor.a = (sf::Uint8) alpha;
    _transitionRect.setFillColor(_transitionColor);
    _screenManager.Window.setView(_defaultCam);
    _screenManager.Window.draw(_transitionRect);
}
