#include "JumpyScreen.hpp"
#include <iostream>
#include "../Factories/Player.hpp"

using namespace ild;

JumpyScreen::JumpyScreen(ScreenManager & manager) 
    : AbstractScreen(manager)
{
    _systems = std::unique_ptr<JumpyGameSystems>(new JumpyGameSystems(manager.Window));
}

void JumpyScreen::Init()
{
    player = JumpyPlayer::Create(_systems.get());
}

void JumpyScreen::Update(float delta)
{
    _systems->GetManager().Update(delta,UpdateStep::Update);
    _systems->GetManager().Update(delta,UpdateStep::Input);
}

void JumpyScreen::Draw()
{
    _manager.Window.clear(sf::Color::Blue);
    _systems->GetManager().Update(0,UpdateStep::Draw);
}
