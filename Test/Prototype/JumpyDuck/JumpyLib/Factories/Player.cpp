#include "Player.hpp"

using namespace ild;

Entity JumpyPlayer::Create(JumpyGameSystems *gameSystems)
{
    auto entity = gameSystems->systemManager().GetEntity("player");
    auto physicsComponent = gameSystems->physics()[entity];

    //Set up input
    auto inputHandler = new JumpyKeyboard();
    inputHandler->SetSystems(gameSystems);
    
    auto controlComponent = new JumpyInputComponent(entity, *physicsComponent, *inputHandler);
    gameSystems->input().AddComponent(entity, controlComponent);

    return entity;
}

