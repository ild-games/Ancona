#ifndef Prototype_JumpyDuck_Factories_Environment_hpp
#define Prototype_JumpyDuck_Factories_Environment_hpp

#include "../Systems/JumpyGameSystems.hpp"

namespace ild
{

namespace JumpyEnvironment
{

Entity CreateEnvironmentBody(
        JumpyGameSystems * gameSystems, 
        Point position = Point(100,200), 
        Point size = Point(250, 10));
Entity CreateSolidBody(JumpyGameSystems * gameSystems);

}

}

#endif
