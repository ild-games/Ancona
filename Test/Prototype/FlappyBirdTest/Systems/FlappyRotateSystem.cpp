#include "FlappyRotateSystem.hpp"
#include <Ancona/Engine/EntityFramework/UpdateStep.hpp>

using namespace ild;

FlappyRotateSystem::FlappyRotateSystem(SystemManager & manager)
    : UnorderedSystem(manager, UpdateStep::Update)
{
}

void FlappyRotateSystem::Update(float delta)
{
    for(EntityComponentPair component : *this)
    {
        component.second->Update();
    }
}

FlappyRotateComponent * FlappyRotateSystem::CreateComponent(
        const Entity & entity,
        SpriteComponent & spriteComponent,
        PositionComponent & positionComponent)
{
    auto comp = new FlappyRotateComponent(spriteComponent, positionComponent);
    AttachComponent(entity, comp);
    return comp;
}
