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
    DeleteQueuedEntities();
}

void SystemManager::DeleteEntity(Entity entity)
{
    Assert(_components.find(entity) != _components.end(), 
            "Cannot delete an entity that is not managed by the system manager");

    for(AbstractSystem * system : _components.at(entity))
    {
        system->EntityIsDeleted(entity);
    }

    auto reverseIter = _entitiesReverse.find(entity);
    if(reverseIter != _entitiesReverse.end())
    {
        _entities.erase(reverseIter->second);
        _entitiesReverse.erase(reverseIter);
    }

    _components.erase(entity);
}

void SystemManager::QueueDelete(Entity entity)
{
    _deleteQueue.push_back(entity);
}

Entity SystemManager::CreateEntity()
{
    Assert(_maxEntityId != ~0u, "Entity key has overflown");

    Entity entity = _maxEntityId++;

    //Create a structure for the entity
    _components[entity];

    return entity;
}

Entity SystemManager::CreateEntity(const std::string & key)
{
    Assert(_entities.find(key) == _entities.end(), "Cannot use the same key for two entities.");

    Entity entity = CreateEntity();
    _entities[key] = entity;
    _entitiesReverse[entity] = key;

    return entity;
}

Entity SystemManager::GetEntity(const std::string & key)
{
    auto entityIter = _entities.find(key);
    if(entityIter == _entities.end())
    {
        return nullentity;
    }
    return entityIter->second; 
}

bool SystemManager::ContainsName(std::string & systemName)
{
    return std::any_of(
            _keyedSystems.begin(), 
            _keyedSystems.end(), 
            [=](std::pair<std::string, AbstractSystem *> & nameSystemPair)
            {
                return nameSystemPair.first == systemName;
            });
}

void SystemManager::RegisterSystem(
        std::string systemName,
        AbstractSystem * system, 
        UpdateStepEnum updateStep)
{
    auto & systems = _systems[updateStep]; 
    Assert(std::find(systems.begin(),systems.end(),system) == systems.end(),
            "A System Manager cannot contain the same system twice");

    systems.push_back(system);

    if(systemName != "")
    {
        Assert(!ContainsName(systemName), "System name must be unique.");
        _keyedSystems.emplace_back(systemName, system);
    }
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

void SystemManager::DeleteQueuedEntities()
{
    for(Entity & entity : _deleteQueue)
    {
        DeleteEntity(entity); 
    }
    _deleteQueue.clear();
}
