#include <algorithm>
#include <map>
#include <unordered_map>

#include <Ancona/Engine/EntityFramework/AbstractSystem.hpp>
#include <Ancona/Engine/EntityFramework/Entity.hpp>
#include <Ancona/Engine/EntityFramework/SystemManager.hpp>
#include <Ancona/Engine/EntityFramework/UpdateStep.hpp>
#include <Ancona/Util/Assert.hpp>

using namespace ild;

SystemManager::SystemManager()
{
    _maxEntityId = 0;
}

void SystemManager::Update(float delta, UpdateStepEnum updateStep)
{
    for(AbstractSystem * system : _systems[updateStep])
    {
        system->Update(delta);
    }
}

void SystemManager::DeleteEntity(Entity entity)
{
    Assert(_components.find(entity) != _components.end(), 
            "Cannot delete an entity that is not managed by the system manager");

    for(AbstractSystem * system : _components.at(entity))
    {
        system->EntityIsDeleted(entity);
    }

    _components.erase(entity);
}

Entity SystemManager::CreateEntity()
{
    Assert(_maxEntityId != ~0, "Entity key has overflown");

    Entity entity = _maxEntityId++;

    //Create a structure for the entity
    _components[entity];

    return entity;
}

void SystemManager::RegisterSystem(AbstractSystem * system, UpdateStepEnum updateStep)
{
    auto & systems = _systems[updateStep]; 
    Assert(std::find(systems.begin(),systems.end(),system) == systems.end(),
            "A System Manager cannot contain the same system twice");

    systems.push_back(system);
}

void SystemManager::RegisterComponent(Entity entity, AbstractSystem * owningSystem)
{
    Assert(_components.find(entity) != _components.end(),
            "Cannot add a component to an entity that does not exist");
   _components[entity].insert(owningSystem); 
}

void SystemManager::UnregisterComponent(Entity entity, AbstractSystem * owningSystem)
{
    Assert(_components.find(entity) != _components.end(),
            "Can not remove a component from an entity that does not exist");
    Assert(_components[entity].find(owningSystem) != _components[entity].end(),
            "Can not remove a component that does not exist");

    _components[entity].erase(owningSystem);
}
