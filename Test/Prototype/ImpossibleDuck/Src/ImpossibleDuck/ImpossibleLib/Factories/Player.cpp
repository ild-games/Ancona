#include "Player.hpp"
#include "../Screens/ImpossibleScreen.hpp"

using namespace ild;

Entity ImpossiblePlayer::Create(ImpossibleGameSystems *gameSystems, ImpossibleInputHandler * inputHandler)
{
    auto entity = gameSystems->systemManager().GetEntity("player");

    //Setup input
    inputHandler->systems(gameSystems);
    auto controlComponent = new ImpossibleInputComponent(entity, *gameSystems, *inputHandler);
    gameSystems->input().AddComponent(entity, controlComponent);

    //Setup collisions
    gameSystems->collision().DefineCollisionCallback(
            gameSystems->collision().GetType("player-type"),
            gameSystems->collision().GetType("ground-type"),
            ImpossiblePlayer::PlayerToGroundCollisionHandler(gameSystems));
    gameSystems->collision().DefineCollisionCallback(
            gameSystems->collision().GetType("player-type"),
            gameSystems->collision().GetType("death-type"),
            ImpossiblePlayer::PlayerToDeathCollisionHandler(gameSystems, inputHandler));

    return entity;
}

std::function<void(Entity player, Entity ground)> ImpossiblePlayer::PlayerToGroundCollisionHandler(ImpossibleGameSystems * systems)
{
    return[systems](Entity player, Entity ground)
    {
        systems->camera().at(systems->systemManager().GetEntity("screen-cam"))->follows(player);
        systems->drawable().at(player)->GetDrawable("player-jump-animation")->inactive(true);
        systems->drawable().at(player)->GetDrawable("player-walk-animation")->inactive(false);
    };
}

std::function<void(Entity player, Entity death)> ImpossiblePlayer::PlayerToDeathCollisionHandler(ImpossibleGameSystems * systems, ImpossibleInputHandler * inputHandler)
{
    return[systems, inputHandler](Entity player, Entity death)
    {
        systems->screenManager().Replace(
                new ImpossibleScreen(systems->screenManager(), inputHandler));
    };
}
