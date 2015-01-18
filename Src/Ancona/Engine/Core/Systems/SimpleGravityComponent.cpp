#include <Ancona/Engine/Core/Systems/SimpleGravityComponent.hpp>
#include <Ancona/Util/VectorMath.hpp>

#include <SFML/System.hpp>

using namespace ild;

SimpleGravityComponent::SimpleGravityComponent(PositionComponent & positionComponent)
    : _positionComponent(positionComponent),
      ROTATION_D(0.0f)
{
}

SimpleGravityComponent::SimpleGravityComponent(
        PositionComponent & positionComponent, 
        float rotationDegrees)
    : _positionComponent(positionComponent),
      ROTATION_D(rotationDegrees)
{
}

void SimpleGravityComponent::Update(float delta)
{
    sf::Vector3f gravVect;
    gravVect.y += (GRAVITY_F * delta);
    gravVect = vector::Rotate(
            gravVect, 
            vector::DegreesToRadians(ROTATION_D));
    _positionComponent.Velocity += gravVect;
}
