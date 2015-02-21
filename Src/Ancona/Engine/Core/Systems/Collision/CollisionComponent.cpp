#include <Ancona/Engine/Core/Systems/Collision/CollisionComponent.hpp>

using namespace ild;

CollisionComponent::CollisionComponent(BasePhysicsComponent & position, 
        const sf::Vector3f & dim,
        CollisionType type,
        BodyTypeEnum bodyType)
    : _position(position), _dim(dim.x,dim.y), _type(type), _bodyType(bodyType)
{
    
}

bool CollisionComponent::Collides(const CollisionComponent & otherComponent)
{
    return _dim.Intersects(otherComponent._dim);
}

void CollisionComponent::Update()
{
    auto & pos = _position.GetInfo().GetPosition();
    _dim.SetPosition(pos.x, pos.y);
}

CollisionType CollisionComponent::GetType()
{
    return _type;
}
