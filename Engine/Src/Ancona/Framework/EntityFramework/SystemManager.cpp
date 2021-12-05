#include <map>
#include <unordered_map>

#include <Ancona/Framework/EntityFramework/AbstractSystem.hpp>
#include <Ancona/Framework/EntityFramework/SystemManager.hpp>
#include <Ancona/Framework/Serializing/Serializing.hpp>
#include <Ancona/Util/Algorithm.hpp>

using namespace ild;

SystemManager::SystemManager()
{
    _maxEntityId = 0;
}

void SystemManager::PreUpdate(UpdateStepEnum updateStep)
{
    if (_systemsNeedInit)
    {
        InitSystems();
    }

    FetchWaitingDependencies();
    for (auto &system : _systems[updateStep])
    {
        system->PreUpdate();
    }
}

void SystemManager::Update(float delta, UpdateStepEnum updateStep)
{
    if (_systemsNeedInit)
    {
        InitSystems();
    }

    FetchWaitingDependencies();
    for (auto &system : _systems[updateStep])
    {
        system->Update(delta);
    }
}

void SystemManager::InitSystems()
{
    _systemsNeedInit = false;
    for (int updateStepInt = 0; updateStepInt != UpdateStep::UpdateStep::LAST_FOR_ITERATION; updateStepInt++)
    {
        UpdateStep::UpdateStep updateStep = static_cast<UpdateStep::UpdateStep>(updateStepInt);
        for (auto &system : _systems[updateStep])
        {
            system->Init();
        }
    }
}

void SystemManager::PostUpdate()
{
    for (int updateStepInt = 0; updateStepInt != UpdateStep::UpdateStep::LAST_FOR_ITERATION; updateStepInt++)
    {
        UpdateStep::UpdateStep updateStep = static_cast<UpdateStep::UpdateStep>(updateStepInt);
        for (auto &system : _systems[updateStep])
        {
            system->DeleteQueuedComponents();
        }
    }
    DeleteQueuedEntities();
}

void SystemManager::DeleteEntity(Entity entity)
{
    ILD_Assert(_components.find(entity) != _components.end(),
               "Cannot delete an entity that is not managed by the system manager");

    for (AbstractSystem *system : _components.at(entity))
    {
        system->EntityIsDeleted(entity);
    }

    if (_entities.ContainsValue(entity))
    {
        _entities.RemoveByValue(entity);
    }

    _components.erase(entity);
}

Entity SystemManager::CopyEntity(const std::string &fromKey)
{
    auto fromEntity = GetEntity(fromKey);
    ILD_Assert(fromEntity != nullentity, "Cannot copy an entity that does not exist");

    auto toEntity = CreateEntity();
    for (AbstractSystem *system : _components.at(fromEntity))
    {
        system->CopyComponentToEntity(fromEntity, toEntity);
    }
    return toEntity;
}

void SystemManager::QueueDeleteEntity(Entity entity)
{
    _deleteQueue.push_back(entity);
}

Entity SystemManager::CreateEntity()
{
    ILD_Assert(_maxEntityId != ~0u, "Entity key has overflown");

    Entity entity = _maxEntityId++;

    // Create a structure for the entity
    _components[entity];

    return entity;
}

Entity SystemManager::CreateEntity(const std::string &key)
{
    ILD_Assert(!_entities.ContainsKey(key), "Cannot use the same key for two entities.");

    Entity entity = CreateEntity();
    _entities.Add(key, entity);

    return entity;
}

Entity SystemManager::GetEntity(const std::string &key)
{
    if (!_entities.ContainsKey(key))
    {
        return nullentity;
    }
    return _entities.GetValue(key);
}

std::string SystemManager::GetEntityKey(const Entity &entity)
{
    return _entities.GetKey(entity);
}

bool SystemManager::ContainsName(std::string &systemName)
{
    return alg::any_of(_keyedSystems, [=](std::pair<std::string, AbstractSystem *> &nameSystemPair) {
        return nameSystemPair.first == systemName;
    });
}

void SystemManager::RegisterSystem(std::string systemName, AbstractSystem *system, UpdateStepEnum updateStep)
{
    auto &systems = _systems[updateStep];
    ILD_Assert(!alg::count_if(systems, [system](std::unique_ptr<AbstractSystem> &ptr) { return ptr.get() == system; }),
               "A System Manager cannot contain the same system twice");

    systems.emplace_back(system);

    if (systemName != "")
    {
        ILD_Assert(!ContainsName(systemName), "System name must be unique.");
        _keyedSystems.emplace_back(systemName, system);
    }
}

void SystemManager::RegisterComponent(Entity entity, AbstractSystem *owningSystem)
{
    ILD_Assert(_components.find(entity) != _components.end(),
               "Cannot add a component to an entity that does not exist");
    _components[entity].insert(owningSystem);
    _needDependencyFetch.emplace_back(entity, owningSystem);
}

void SystemManager::UnregisterComponent(Entity entity, AbstractSystem *owningSystem)
{
    ILD_Assert(_components.find(entity) != _components.end(),
               "Can not remove a component from an entity that does not exist");
    ILD_Assert(_components[entity].find(owningSystem) != _components[entity].end(),
               "Can not remove a component that does not exist");

    _components[entity].erase(owningSystem);
}

void SystemManager::AddEntitySaveableSystemPair(std::string entity, std::string system)
{
    ILD_Assert(_entities.ContainsKey(entity),
               "Cannot add entity-system saveable pair: Entity " + entity + " does not exist.");
    ILD_Assert(alg::count_if(_keyedSystems,
                             [system](std::pair<std::string, AbstractSystem *> sysNamePair) {
                                 return sysNamePair.first == system;
                             }),
               "Cannot add entity-system saveable pair: System " + system + " does not exist or is not keyed.");

    if (!alg::count(_entitySaveableSystems[system], entity))
    {
        _entitySaveableSystems[system].push_back(entity);
    }
}

void SystemManager::DeleteQueuedEntities()
{
    for (Entity &entity : _deleteQueue)
    {
        DeleteEntity(entity);
    }
    _deleteQueue.clear();
}

void SystemManager::FetchWaitingDependencies()
{
    for (auto &entitySystemPair : _needDependencyFetch)
    {
        entitySystemPair.second->FetchComponentDependencies(entitySystemPair.first);
    }
    _needDependencyFetch.clear();
}

void SystemManager::Serialize(Archive &arc)
{
}
