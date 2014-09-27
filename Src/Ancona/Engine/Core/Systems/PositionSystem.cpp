#include <Ancona/Engine/Core/Systems/PositionSystem.hpp>
#include <Ancona/Engine/EntityFramework/UpdateStep.hpp>

using namespace ild;

PositionSystem::PositionSystem(SystemManager & manager)
    : UnorderedSystem(manager, UpdateStep::Update)
{
}

void PositionSystem::Update(float delta)
{
    for(EntityComponentPair component : *this)
    {
        component.second->Update();
    }
}

PositionComponent * PositionSystem::CreateComponent(
        const Entity & entity,
        const sf::Vector3f & initialPosition,
        const sf::Vector3f & initialVelocity) 
{
    auto comp = new PositionComponent(initialPosition, initialVelocity);
    AttachComponent(entity, comp);
    return comp;
}
