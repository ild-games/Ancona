#include "PathSystem.hpp"

using namespace ild;

/* Component */
PathComponent::PathComponent()
{
}

void PathComponent::Update(float delta)
{
}

void PathComponent::Serialize(Archive & arc)
{
    arc(_startVertex, "_startVertex");
    arc(_endVertex, "_endVertex");
}

void PathComponent::FetchDependencies(const Entity &entity)
{
}

/* System */
PathSystem::PathSystem(
        std::string name,
        SystemManager &manager) :
    UnorderedSystem(name, manager, UpdateStep::Update)
{
}

void PathSystem::Update(float delta)
{
    for (EntityComponentPair comp : *this)
    {
        comp.second->Update(delta);
    }
}

PathComponent * PathSystem::CreateComponent(const Entity &entity)
{
    PathComponent * comp = new PathComponent();
    AttachComponent(entity, comp);
    return comp;
}
