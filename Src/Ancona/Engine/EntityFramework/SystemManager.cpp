#include <unordered_map>
#include <map>

#include <Ancona/Engine/EntityFramework/AbstractSystem.hpp>
#include <Ancona/Engine/EntityFramework/Entity.hpp>
#include <Ancona/Engine/EntityFramework/SystemManager.hpp>
#include <Ancona/Engine/EntityFramework/UpdateStep.hpp>

using namespace ild;

SystemManager::SystemManager()
{
    _maxEntityId = 0;
}

void SystemManager::Update(float delta, UpdateStepEnum updateStep)
{
    for(AbstractSystem * system : _systems.at(updateStep))
    {
        system->Update(delta);
    }
}

void SystemManager::DeleteEntity(Entity entity)
{
    for(AbstractSystem * system : _components.at(entity))
    {
        system->EntityIsDeleted(entity);
    }
    _components.erase(entity);
}

Entity SystemManager::CreateEntity()
{
    return _maxEntityId++;
}

void SystemManager::RegisterSystem(AbstractSystem * system, UpdateStepEnum updateStep)
{
    _systems[updateStep].push_back(system);
}

void SystemManager::RegisterComponent(Entity entity, AbstractSystem * owningSystem)
{
   _components[entity].insert(owningSystem); 
}

void SystemManager::UnregisterComponent(Entity entity, AbstractSystem * owningSystem)
{
    _components[entity].erase(owningSystem);
}
