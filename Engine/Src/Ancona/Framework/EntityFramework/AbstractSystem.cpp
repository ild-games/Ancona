#include <Ancona/Framework/EntityFramework/AbstractSystem.hpp>
#include <Ancona/Framework/EntityFramework/SystemManager.hpp>
#include <Ancona/Framework/EntityFramework/UpdateStep.hpp>

using namespace ild;

AbstractSystem::AbstractSystem(
        std::string systemName,
        SystemManager & systemManager,
        UpdateStepEnum updateStep) :
    _systemManager(systemManager),
    _systemName(systemName)
{
    systemManager.RegisterSystem(systemName, this, updateStep);
}
