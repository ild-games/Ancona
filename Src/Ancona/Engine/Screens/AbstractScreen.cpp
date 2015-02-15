#include <Ancona/Engine/Screens/AbstractScreen.hpp>
#include <Ancona/Engine/Screens/LoadingScreen.hpp>

using namespace ild;

AbstractScreen::AbstractScreen(ScreenManager & manager) : 
    __Initialized(false),
    __Entering(false),
    __Exiting(false),
    _manager(manager),
    _transitionColor(0, 0, 0, 255),
    _transitionRect(sf::Vector2f(_manager.Window.getSize().x, _manager.Window.getSize().y)),
    _defaultCam(new sf::View(_manager.Window.getView())) 
{
}

AbstractScreen::~AbstractScreen()
{
    delete _defaultCam;
}

void AbstractScreen::Entering(float delta)
{
    int alpha = _transitionColor.a;
    alpha -= (TRANSITION_SPEED * delta);
    if(alpha < 0) 
    {
        alpha = 0;
        __Entering = false; 
    }
    _transitionColor.a = alpha;
    _transitionRect.setFillColor(_transitionColor);
    _manager.Window.setView(*_defaultCam);
    _manager.Window.draw(_transitionRect);
}

void AbstractScreen::Exiting(float delta)
{
    int alpha = _transitionColor.a;
    alpha += (TRANSITION_SPEED * delta);
    if(alpha > 255) 
    {
        alpha = 255;
        __Exiting = false; 
    }
    _transitionColor.a = alpha;
    _transitionRect.setFillColor(_transitionColor);
    _manager.Window.setView(*_defaultCam);
    _manager.Window.draw(_transitionRect);
}
