#include <Ancona/Engine/Core/Systems/PositionComponent.hpp>

using namespace ild;

PositionComponent::PositionComponent(const sf::Vector3f & position, const sf::Vector3f & velocity)
    : _position(position), _velocity(velocity)
{
}

sf::Vector3f & PositionComponent::Position()
{
    return _position;
}

sf::Vector3f & PositionComponent::Velocity()
{
    return _velocity;
}

void PositionComponent::Update()
{
    _position += _velocity;
}
