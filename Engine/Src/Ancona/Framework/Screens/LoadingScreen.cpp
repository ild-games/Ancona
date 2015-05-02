#include <SFML/Window.hpp>

#include <Ancona/Framework/Screens/LoadingScreen.hpp>
#include <Ancona/Framework/Resource/ResourceLibrary.hpp>

using namespace ild;

LoadingScreen::LoadingScreen(
        AbstractScreen * screenLoading,
        ScreenManager & manager) :
    AbstractScreen("loading", manager),
    _screenLoading(screenLoading)
{
    _systemsContainer = std::unique_ptr<ScreenSystemsContainer>(new ScreenSystemsContainer(manager));
    _mapLoader.reset(new MapSerializer(
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
    _screenManager.Window.clear(sf::Color::Green);
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
