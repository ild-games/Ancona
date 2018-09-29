#include <fstream>
#include <iostream>

#include <Ancona/Framework/Screens/AbstractScreen.hpp>

using namespace ild;

AbstractScreen::AbstractScreen(
        std::string key,
        ScreenManager & screenManager,
        std::shared_ptr<RequestList> requestList) :
    __Initialized(false),
    __Entering(false),
    __Exiting(false),
    _screenManager(screenManager),
    KEY(key),
    _transitionColor(0, 0, 0, 255),
    _transitionRect(sf::Vector2f(_screenManager.windowWidth() * 5, _screenManager.windowHeight() * 5)),
    _defaultCam(sf::View(_screenManager.Window.getDefaultView())),
    _requestList(requestList)
{
}

AbstractScreen::~AbstractScreen()
{
    if (_requestList != nullptr)
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
