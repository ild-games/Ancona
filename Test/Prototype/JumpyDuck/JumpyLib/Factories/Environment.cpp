#include "Environment.hpp"

using namespace ild;

Entity JumpyEnvironment::CreateEnvironmentBody(JumpyGameSystems * gameSystems)
{
    auto entity = gameSystems->GetManager().CreateEntity();
    auto physicsComponent = gameSystems->GetPhysics().CreateComponent(entity);

    return 0;
}

Entity JumpyEnvironment::CreateSolidBody(JumpyGameSystems * gameSystems)
{

    return 0;
}
