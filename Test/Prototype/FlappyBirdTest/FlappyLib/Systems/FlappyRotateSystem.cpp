#include "FlappyRotateSystem.hpp"
#include <Ancona/Framework/EntityFramework/UpdateStep.hpp>

using namespace ild;

FlappyRotateSystem::FlappyRotateSystem(SystemManager & manager)
    : UnorderedSystem(manager, UpdateStep::Update)
{
}

void FlappyRotateSystem::Update(float delta)
{
    for(EntityComponentPair component : *this)
    {
        component.second->Update(delta);
    }
}

FlappyRotateComponent * FlappyRotateSystem::CreateComponent(
        const Entity & entity,
        DrawableComponent & drawableComponent,
        PositionComponent & positionComponent)
{
    auto comp = new FlappyRotateComponent(drawableComponent, positionComponent);
    AttachComponent(entity, comp);
    return comp;
}
