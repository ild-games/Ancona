#ifndef ImpossibleDuck_ImpossibleLib_Factories_Player_hpp
#define ImpossibleDuck_ImpossibleLib_Factories_Player_hpp

#include "../Systems/ImpossibleGameSystems.hpp"

namespace ild 
{

namespace ImpossiblePlayer
{

Entity Create(ImpossibleGameSystems * gameSystems, ImpossibleInputHandler * inputHandler);
std::function<void(Entity player, Entity ground)> PlayerToGroundCollisionHandler(ImpossibleGameSystems * systems);
std::function<void(Entity player, Entity death)> PlayerToDeathCollisionHandler(
        ImpossibleGameSystems * systems,
        ImpossibleInputHandler * inputHandler);

}

}

#endif
