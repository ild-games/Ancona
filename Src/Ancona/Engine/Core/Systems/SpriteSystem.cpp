#include <Ancona/Engine/Core/Systems/SpriteSystem.hpp>
#include <Ancona/Engine/Core/Systems/SpriteComponent.hpp>
#include <Ancona/Engine/EntityFramework/UpdateStep.hpp>

#include <iostream>

using namespace ild;

SpriteSystem::SpriteSystem(
        sf::RenderWindow & window, 
        SystemManager & systemManager, 
        PositionSystem & positionSystem)
    : UnorderedSystem(systemManager,UpdateStep::Draw), _window(window), _positionSystem(positionSystem)
{
}


SpriteComponent * SpriteSystem::CreateComponent(
        const Entity & entity, 
        const std::string & textureKey,
        const RenderPriorityEnum priority,
        int priorityOffset)
{
    auto positionComponent = _positionSystem[entity];

    Assert(
            positionComponent != nullptr,
            "A sprite component can only be attached to an entity with a position component");

    SpriteComponent * component = new SpriteComponent(
            *positionComponent,
            textureKey,
            priority,
            priorityOffset);

    AttachComponent(entity, component);

    _renderQueue.push_back(component);
    std::sort(
            _renderQueue.begin(), 
            _renderQueue.end(), 
            [](SpriteComponent * lhs, SpriteComponent * rhs)
            {
                return (lhs->GetRenderPriority() + lhs->GetPriorityOffset()) <
                       (rhs->GetRenderPriority() + rhs->GetPriorityOffset());
            });

    return component;
}

void SpriteSystem::OnComponentRemove(Entity entity, SpriteComponent * component)
{
    _renderQueue.erase(std::remove(_renderQueue.begin(), _renderQueue.end(), component), _renderQueue.end());
}

void SpriteSystem::Update(float delta)
{
    for(SpriteComponent * spriteComp : _renderQueue)
    {
        spriteComp->Draw(_window);
    }
}

