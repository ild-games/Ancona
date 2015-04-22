#include "Environment.hpp"

using namespace ild;

void ImpossibleEnvironment::SetupCollisions(ImpossibleGameSystems *gameSystems)
{
    gameSystems->collision().DefineCollisionCallback(
            gameSystems->collision().GetType("ground-type"),
            gameSystems->collision().GetType("ground-warp-type"),
            ImpossibleEnvironment::GroundToGroundWarpCollisionHandler(gameSystems));
}

std::function<void(Entity ground, Entity groundWarp)> ImpossibleEnvironment::GroundToGroundWarpCollisionHandler(ImpossibleGameSystems * systems)
{
    return[systems](Entity ground, Entity groundWarp)
    {
        Point oldLoc = systems->physics().at(ground)->GetMutableInfo().position();
        oldLoc.x = 800;
        systems->physics().at(ground)->GetMutableInfo().position(oldLoc);
    };
}
