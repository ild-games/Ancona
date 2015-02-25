#include "JumpyScreen.hpp"
#include <iostream>
#include "../Factories/Player.hpp"
#include "../Factories/Environment.hpp"

using namespace ild;

JumpyScreen::JumpyScreen(ScreenManager & manager) 
    : AbstractScreen(manager)
{
    _systems = std::unique_ptr<JumpyGameSystems>(new JumpyGameSystems(manager.Window));
}

void JumpyScreen::Init()
{
    defaultCam = _systems->GetManager().CreateEntity();
    CameraComponent * cam = _systems->GetCamera().CreateComponent(
            defaultCam, 
            _manager.Window.getView(),
            0);
    _systems->GetDrawable().SetDefaultCamera(cam);
    player = JumpyPlayer::Create(_systems.get());
    JumpyEnvironment::CreateSolidBody(_systems.get());
    JumpyEnvironment::CreateEnvironmentBody(_systems.get());
}

void JumpyScreen::Update(float delta)
{
    _systems->GetManager().Update(delta,UpdateStep::Update);
    _systems->GetManager().Update(delta,UpdateStep::Input);
}

void JumpyScreen::Draw(float delta)
{
    _manager.Window.clear(sf::Color::Blue);
    _systems->GetManager().Update(0,UpdateStep::Draw);
}
