#include "PathFollowerSystem.hpp"

using namespace ild;

/* Component */
PathFollowerComponent::PathFollowerComponent()
{
}

void PathFollowerComponent::Update(float delta)
{
}

void PathFollowerComponent::Serialize(Archive & arc)
{
    arc.entityUsingJsonKey(_pathEntity, "pathEntity");
    arc.system(_pathSystem, "path");
    arc.system(_positionSystem, "position");
}

void PathFollowerComponent::FetchDependencies(const Entity &entity)
{
    _pathComponent = _pathSystem->at(_pathEntity);
    _positionComponent = _positionSystem->at(entity);
}

/* System */
PathFollowerSystem::PathFollowerSystem(
        std::string name,
        SystemManager &manager) :
    UnorderedSystem(name, manager, UpdateStep::Update)
{
}

void PathFollowerSystem::Update(float delta)
{
    for (EntityComponentPair comp : *this)
    {
        comp.second->Update(delta);
    }
}

PathFollowerComponent * PathFollowerSystem::CreateComponent(const Entity &entity)
{
    PathFollowerComponent * comp = new PathFollowerComponent();
    AttachComponent(entity, comp);
    return comp;
}
