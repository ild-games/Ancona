#include <Ancona/Engine/EntityFramework/AbstractSystem.hpp>
#include <Ancona/Engine/EntityFramework/SystemManager.hpp>
#include <Ancona/Engine/EntityFramework/UpdateStep.hpp>

using namespace ild;

AbstractSystem::AbstractSystem(
        SystemManager & systemManager,
        UpdateStepEnum updateStep) :
    _systemManager(systemManager)
{
    systemManager.RegisterSystem(this, updateStep);
}
