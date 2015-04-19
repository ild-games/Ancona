#include "Player.hpp"

using namespace ild;

Entity JumpyPlayer::Create(JumpyGameSystems *gameSystems)
{
    auto entity = gameSystems->GetSystemManager().GetEntity("player");
    auto physicsComponent = gameSystems->GetPhysics()[entity];

    //Set up input
    auto inputHandler = new JumpyKeyboard();
    inputHandler->SetSystems(gameSystems);
    
    auto controlComponent = new JumpyInputComponent(entity, *physicsComponent, *inputHandler);
    gameSystems->GetInput().AddComponent(entity, controlComponent);

    return entity;
}

