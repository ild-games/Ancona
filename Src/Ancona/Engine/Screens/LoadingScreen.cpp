#include <SFML/Window.hpp>

#include <Ancona/Engine/Screens/LoadingScreen.hpp>
#include <Ancona/Engine/Resource/ResourceLibrary.hpp>

using namespace ild;

LoadingScreen::LoadingScreen(
        AbstractScreen * screenLoading,
        ScreenManager & manager) :
    AbstractScreen(manager, "loading"),
    _screenLoading(screenLoading)
{
    _mapLoader.reset(new MapLoader(
                screenLoading->GetKey(),
                screenLoading->GetSystems()));
}

void LoadingScreen::Update(float delta)
{
    _mapLoader->ContinueLoading();
}

void LoadingScreen::Draw(float delta)
{
    _manager.Window.clear(sf::Color::White);
    sf::RectangleShape outerBar(sf::Vector2f(750, 30));
    outerBar.setFillColor(sf::Color::Transparent);
    outerBar.setOutlineThickness(1.0f);
    outerBar.setOutlineColor(sf::Color::Black);
    outerBar.setPosition(25, 10);
    sf::RectangleShape innerBar(sf::Vector2f(750 * _mapLoader->PercentLoaded(), 30));
    innerBar.setFillColor(sf::Color::Blue);
    innerBar.setOutlineColor(sf::Color::Blue);
    innerBar.setPosition(25, 10);
    _manager.Window.draw(innerBar);
    _manager.Window.draw(outerBar);
}

void LoadingScreen::Entering(float delta)
{
    __Entering = false;
}

void LoadingScreen::Exiting(float delta)
{
    __Exiting = false;
}
