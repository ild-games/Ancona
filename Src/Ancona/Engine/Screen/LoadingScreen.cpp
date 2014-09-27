#include <SFML/Window.hpp>

#include <Ancona/Engine/Screen/LoadingScreen.hpp>
#include <Ancona/Engine/Resource/RequestList.hpp>
#include <Ancona/Engine/Resource/ResourceLibrary.hpp>

#include <iostream>

using namespace ild;

LoadingScreen::LoadingScreen(ScreenManager & manager, RequestList & requestList)
    : AbstractScreen(manager), _requestList(requestList)
{
}

void LoadingScreen::Update(float delta)
{
    if(ResourceLibrary::DoneLoading(_requestList)) 
    {
        _manager.Pop();
    }
}

void LoadingScreen::Draw()
{
    _manager.Window().clear(sf::Color::White);
    sf::RectangleShape outerBar(sf::Vector2f(750, 30));
    outerBar.setFillColor(sf::Color::Transparent);
    outerBar.setOutlineThickness(1.0f);
    outerBar.setOutlineColor(sf::Color::Black);
    outerBar.setPosition(25, 10);
    sf::RectangleShape innerBar(sf::Vector2f(750 * _requestList.PercentLoaded(), 30));
    innerBar.setFillColor(sf::Color::Blue);
    innerBar.setOutlineColor(sf::Color::Blue);
    innerBar.setPosition(25, 10);
    _manager.Window().draw(innerBar);
    _manager.Window().draw(outerBar);
}

