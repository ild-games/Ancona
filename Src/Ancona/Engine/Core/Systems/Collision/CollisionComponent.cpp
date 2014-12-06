#include <Ancona/Engine/Core/Systems/Collision/CollisionComponent.hpp>

using namespace ild;

CollisionComponent::CollisionComponent(PositionComponent & position, 
        const sf::Vector3f & dim,
        CollisionType type)
    : _position(position), _dim(dim.x,dim.y)
{

}

bool CollisionComponent::Collides(const CollisionComponent & otherComponent)
{
    return _dim.Intersects(otherComponent._dim);
}

void CollisionComponent::Update()
{
    auto & pos = _position.Position;
    _dim.SetPosition(pos.x, pos.y);
}
