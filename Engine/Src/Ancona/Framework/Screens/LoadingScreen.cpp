#include <Ancona/Framework/Resource/ResourceLibrary.hpp>
#include <Ancona/Framework/Screens/LoadingScreen.hpp>
#include <Ancona/Graphics/Color.hpp>

using namespace ild;

LoadingScreen::LoadingScreen(AbstractScreen *screenLoading, ScreenManager &manager)
    : AbstractScreen("loading", manager), _screenLoading(screenLoading)
{
    _systemsContainer = std::unique_ptr<ScreenSystemsContainer>(new ScreenSystemsContainer(manager));
    _mapLoader.reset(new MapSerializer(screenLoading->key(), *screenLoading->systemsContainer(),
                                       _screenLoading->requestList(), true));
}

void LoadingScreen::InputUpdate(float delta)
{
}

void LoadingScreen::Update(float delta)
{
    if (!_mapLoader->ContinueLoading())
    {
        _screenManager.Pop();
    }
}

void LoadingScreen::Draw(float delta)
{
    _screenManager.Window.Clear(Color::Black);
}

void LoadingScreen::Entering(float delta)
{
    __Entering = false;
}

void LoadingScreen::Exiting(float delta)
{
    __Exiting = false;
}

ScreenSystemsContainer *LoadingScreen::systemsContainer()
{
    return _systemsContainer.get();
}
