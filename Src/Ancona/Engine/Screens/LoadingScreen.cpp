#include <SFML/Window.hpp>

#include <Ancona/Engine/Screens/LoadingScreen.hpp>
#include <Ancona/Engine/Resource/ResourceLibrary.hpp>

using namespace ild;

LoadingScreen::LoadingScreen(
        AbstractScreen * screenLoading,
        ScreenManager & manager) :
    AbstractScreen("loading", manager),
    _screenLoading(screenLoading)
{
    _systemsContainer = std::unique_ptr<ScreenSystemsContainer>(new ScreenSystemsContainer(manager));
    _mapLoader.reset(new MapLoader(
            screenLoading->key(),
                *screenLoading->systemsContainer()));
}

void LoadingScreen::Update(float delta)
{
    if(!_mapLoader->ContinueLoading())
    {
        _screenLoading->requestList(_mapLoader->requestList());
        _screenManager.Pop();
    }
}

void LoadingScreen::Draw(float delta)
{
    _screenManager.Window.clear(sf::Color::White);
    sf::RectangleShape outerBar(sf::Vector2f(750, 30));
    outerBar.setFillColor(sf::Color::Transparent);
    outerBar.setOutlineThickness(1.0f);
    outerBar.setOutlineColor(sf::Color::Black);
    outerBar.setPosition(25, 10);
    sf::RectangleShape innerBar(sf::Vector2f(750 * _mapLoader->PercentLoaded(), 30));
    innerBar.setFillColor(sf::Color::Blue);
    innerBar.setOutlineColor(sf::Color::Blue);
    innerBar.setPosition(25, 10);
    _screenManager.Window.draw(innerBar);
    _screenManager.Window.draw(outerBar);
}

void LoadingScreen::Entering(float delta)
{
    __Entering = false;
}

void LoadingScreen::Exiting(float delta)
{
    __Exiting = false;
}

ScreenSystemsContainer * LoadingScreen::systemsContainer()
{
    return _systemsContainer.get();
}
