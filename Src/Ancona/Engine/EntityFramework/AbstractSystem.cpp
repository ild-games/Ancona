#include <Ancona/Engine/EntityFramework/AbstractSystem.hpp>
#include <Ancona/Engine/EntityFramework/SystemManager.hpp>
#include <Ancona/Engine/EntityFramework/UpdateStep.hpp>

using namespace ild;

AbstractSystem::AbstractSystem(
        std::string systemName,
        SystemManager & systemManager,
        UpdateStepEnum updateStep) :
    _systemManager(systemManager)
{
    systemManager.RegisterSystem(systemName, this, updateStep);
}
