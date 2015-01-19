#include <Ancona/Engine/Core/Systems/SimpleGravitySystem.hpp>
#include <Ancona/Engine/EntityFramework/UpdateStep.hpp>

using namespace ild;

SimpleGravitySystem::SimpleGravitySystem(SystemManager & manager)
    : UnorderedSystem(manager, UpdateStep::Update)
{
}

void SimpleGravitySystem::Update(float delta)
{
    for(EntityComponentPair component : *this) 
    {
        component.second->Update(delta);
    }
}

SimpleGravityComponent * SimpleGravitySystem::CreateComponent(
        const Entity & entity,
        PositionComponent & positionComponent)
{
    auto comp = new SimpleGravityComponent(positionComponent);
    AttachComponent(entity, comp);
    return comp;
}

SimpleGravityComponent * SimpleGravitySystem::CreateComponent(
        const Entity & entity,
        PositionComponent & positionComponent,
        float degreeRotation)
{
    auto comp = new SimpleGravityComponent(positionComponent, degreeRotation);
    AttachComponent(entity, comp);
    return comp;
}
