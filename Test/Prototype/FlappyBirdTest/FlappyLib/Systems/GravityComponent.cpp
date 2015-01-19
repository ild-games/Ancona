#include "GravityComponent.hpp"

using namespace ild;

GravityComponent::GravityComponent(PositionComponent & positionComponent)
    : _positionComponent(positionComponent)
{
}

void GravityComponent::Update(float delta)
{
    _positionComponent.Velocity.y += (GRAVITY_F * delta);
}
