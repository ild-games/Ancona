#include "JumpyScreen.hpp"
#include "../Factories/Player.hpp"

using namespace ild;

JumpyScreen::JumpyScreen(ScreenManager & manager) : 
    AbstractScreen("jumpy-game", manager)
{
    _systems = std::unique_ptr<JumpyGameSystems>(new JumpyGameSystems(manager));
}

void JumpyScreen::Init()
{
    player = JumpyPlayer::Create(_systems.get());
}

void JumpyScreen::Update(float delta)
{
    _systems->systemManager().Update(delta,UpdateStep::Update);
    _systems->systemManager().Update(delta,UpdateStep::Input);
}

void JumpyScreen::Draw(float delta)
{
    _screenManager.Window.clear(sf::Color::Blue);
    _systems->systemManager().Update(0,UpdateStep::Draw);
}
