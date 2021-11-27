#include <fstream>
#include <iostream>
#include <sstream>

#include <Ancona/Framework/Screens/AbstractScreen.hpp>
#include <Ancona/System/Log.hpp>

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
    _defaultCam(sf::View(_screenManager.Window.GetDefaultView())),
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

void AbstractScreen::OnEntering()
{
    _transitioningAlpha = 255.0f;
}

void AbstractScreen::OnExiting()
{
    _transitioningAlpha = 0.0f;
}

void AbstractScreen::Entering(float delta)
{
    _transitioningAlpha -= (TRANSITION_SPEED * delta);
    if (_transitioningAlpha < 0.0f)
    {
        _transitioningAlpha = 0.0f;
        __Entering = false;
    }
    _transitionColor.a = (sf::Uint8) _transitioningAlpha;
    _transitionRect.setFillColor(_transitionColor);
    _screenManager.Window.SetView(_defaultCam);
    _screenManager.Window.Draw(_transitionRect);
}

void AbstractScreen::Exiting(float delta)
{
    _transitioningAlpha += (TRANSITION_SPEED * delta);
    if (_transitioningAlpha > 255.0f)
    {
        _transitioningAlpha = 255.0f;
        __Exiting = false;
    }
    _transitionColor.a = (sf::Uint8) _transitioningAlpha;
    _transitionRect.setFillColor(_transitionColor);
    _screenManager.Window.SetView(_defaultCam);
    _screenManager.Window.Draw(_transitionRect);
}
