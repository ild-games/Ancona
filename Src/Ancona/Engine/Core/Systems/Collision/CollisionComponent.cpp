#include <Ancona/Engine/Core/Systems/Collision/CollisionComponent.hpp>

using namespace ild;

CollisionComponent::CollisionComponent(BasePhysicsComponent & position, 
        const sf::Vector3f & dim,
        CollisionType type,
        BodyTypeEnum bodyType)
    : _position(position), _dim(dim.x,dim.y), _type(type), _bodyType(bodyType)
{
    
}

bool CollisionComponent::Collides(const CollisionComponent & otherComponent, Point & fixNormal, float & fixMagnitude)
{
    return _dim.Intersects(otherComponent._dim, fixNormal, fixMagnitude);
}

void CollisionComponent::Update()
{
    auto & info = _position.GetMutableInfo();
    auto & pos = info.GetPosition();
    _dim.SetPosition(pos.x, pos.y);
    info.SetGroundDirection(Point());
}

CollisionType CollisionComponent::GetType()
{
    return _type;
}
