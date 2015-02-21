#include <fstream>

#include <json/json.h>

#include <Ancona/Engine/Screens/AbstractScreen.hpp>

using namespace ild;

AbstractScreen::AbstractScreen(ScreenManager & manager) : 
    __Initialized(false),
    __Entering(false),
    __Exiting(false),
    _manager(manager),
    _transitionColor(0, 0, 0, 255),
    _transitionRect(sf::Vector2f(_manager.Window.getSize().x, _manager.Window.getSize().y)),
    _defaultCam(sf::View(_manager.Window.getView())) 
{
    std::ifstream saveStream("save.dat", std::ifstream::binary);
    Json::Value root;
    saveStream >> root;
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
    _transitionColor.a = (sf::Uint8) alpha;
    _transitionRect.setFillColor(_transitionColor);
    _manager.Window.setView(_defaultCam);
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
    _transitionColor.a = (sf::Uint8) alpha;
    _transitionRect.setFillColor(_transitionColor);
    _manager.Window.setView(_defaultCam);
    _manager.Window.draw(_transitionRect);
}

void AbstractScreen::LoadMap(std::string map)
{
    std::ifstream mapStream(map + ".map", std::ifstream::binary);
}
