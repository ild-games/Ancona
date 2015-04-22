#ifndef ImpossibleDuck_ImpossibleLib_Factories_Environment_hpp
#define ImpossibleDuck_ImpossibleLib_Factories_Environment_hpp

#include "../Systems/ImpossibleGameSystems.hpp"

namespace ild
{

namespace ImpossibleEnvironment
{

void SetupCollisions(ImpossibleGameSystems * gameSystems);
std::function<void(Entity ground, Entity groundWarp)> GroundToGroundWarpCollisionHandler(ImpossibleGameSystems * systems);

}

}

#endif
