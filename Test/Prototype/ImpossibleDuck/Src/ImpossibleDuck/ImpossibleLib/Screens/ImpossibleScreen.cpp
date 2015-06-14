#include "ImpossibleScreen.hpp"
#include "../Factories/Player.hpp"
#include "../Factories/Environment.hpp"

using namespace ild;

ImpossibleScreen::ImpossibleScreen(
        ScreenManager & manager,
        ImpossibleInputHandler * inputHandler) :
    AbstractScreen("impossible-game", manager),
    _inputHandler(inputHandler)
{
    _systems = std::unique_ptr<ImpossibleGameSystems>(new ImpossibleGameSystems(manager));
}

ImpossibleScreen::~ImpossibleScreen()
{
    _inputHandler.release();
}

void ImpossibleScreen::Init()
{
    player = ImpossiblePlayer::Create(_systems.get(), _inputHandler.get());
    ImpossibleEnvironment::CreateCounter(_systems.get());
    ImpossibleEnvironment::SetupCollisions(_systems.get());
}

void ImpossibleScreen::Update(float delta)
{
    _systems->systemManager().Update(delta, UpdateStep::Update);
    _systems->systemManager().Update(delta, UpdateStep::Input);
}

void ImpossibleScreen::Draw(float delta)
{
    _screenManager.Window.clear(sf::Color::Blue);
    _systems->systemManager().Update(delta, UpdateStep::Draw);
}