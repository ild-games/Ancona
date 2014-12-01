#include "GravitySystem.hpp"
#include <Ancona/Engine/EntityFramework/UpdateStep.hpp>

using namespace ild;

GravitySystem::GravitySystem(SystemManager & manager)
    : UnorderedSystem(manager, UpdateStep::Update)
{
}

void GravitySystem::Update(float delta)
{
    for(EntityComponentPair component : *this) 
    {
        component.second->Update(delta);
    }
}

GravityComponent * GravitySystem::CreateComponent(
        const Entity & entity,
        PositionComponent & positionComponent)
{
    auto comp = new GravityComponent(positionComponent);
    AttachComponent(entity, comp);
    return comp;
}
