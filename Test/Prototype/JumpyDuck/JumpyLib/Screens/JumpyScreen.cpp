#include "JumpyScreen.hpp"
#include <iostream>
#include "../Factories/Player.hpp"
#include "../Factories/Environment.hpp"

using namespace ild;

JumpyScreen::JumpyScreen(ScreenManager & manager) : 
    AbstractScreen("jumpy-game", manager)
{
    _systems = std::unique_ptr<JumpyGameSystems>(new JumpyGameSystems(manager));
}

void JumpyScreen::Init()
{
    defaultCam = _systems->GetSystemManager().CreateEntity();
    CameraComponent * cam = _systems->GetCamera().CreateComponent(
            defaultCam, 
            _screenManager.Window.getView(),
            0);
    _systems->GetDrawable().SetDefaultCamera(cam);
    player = JumpyPlayer::Create(_systems.get());
    JumpyEnvironment::CreateSolidBody(_systems.get());
    JumpyEnvironment::CreateEnvironmentBody(_systems.get());
    JumpyEnvironment::CreateEnvironmentBody(_systems.get(),Point(200,100));
}

void JumpyScreen::Update(float delta)
{
    _systems->GetSystemManager().Update(delta,UpdateStep::Update);
    _systems->GetSystemManager().Update(delta,UpdateStep::Input);
}

void JumpyScreen::Draw(float delta)
{
    _screenManager.Window.clear(sf::Color::Blue);
    _systems->GetSystemManager().Update(0,UpdateStep::Draw);
}
