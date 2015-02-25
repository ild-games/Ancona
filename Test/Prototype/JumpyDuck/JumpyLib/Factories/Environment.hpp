#ifndef Prototype_JumpyDuck_Factories_Environment_hpp
#define Prototype_JumpyDuck_Factories_Environment_hpp

#include "../Systems/JumpyGameSystems.hpp"

namespace ild
{

namespace JumpyEnvironment
{

Entity CreateEnvironmentBody(JumpyGameSystems * gameSystems);
Entity CreateSolidBody(JumpyGameSystems * gameSystems);

}

}

#endif
