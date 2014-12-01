#include <Ancona/Engine/Core/Systems/PositionComponent.hpp>

using namespace ild;

PositionComponent::PositionComponent(const sf::Vector3f & position, const sf::Vector3f & velocity)
    : Position(position), Velocity(velocity)
{
}

void PositionComponent::Update(float delta)
{
    Position += (Velocity * delta);
}
