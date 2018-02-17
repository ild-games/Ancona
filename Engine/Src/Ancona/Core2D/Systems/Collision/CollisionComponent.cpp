#include <Ancona/Util/Algorithm.hpp>
#include <Ancona/Util/Math.hpp>
#include <Ancona/Util2D/Collision/Math.hpp>
#include <Ancona/Core2D/Systems/Collision/CollisionComponent.hpp>
#include <Ancona/Core2D/Systems/Collision/CollisionSystem.hpp>

using namespace ild;

static DualMap<std::string, BodyTypeEnum> BodyTypeEnumStringMap {
    { "none", BodyType::None },
    { "solid", BodyType::Solid },
    { "environment", BodyType::Environment }
};

CollisionComponent::CollisionComponent(CollisionSystem * collisionSystem,
        const sf::Vector3f & dim,
        CollisionType type,
        BodyTypeEnum bodyType) :
    _system(collisionSystem), 
    _dim(dim.x,dim.y), 
    _type(type), 
    _bodyType(bodyType)
{
}

std::pair<float, float> Projection(float size, float movement, float position)
{
    if (movement < 0) {
        return std::pair<float, float>(position, position + size - movement); 
    } else {
        return std::pair<float, float>(position - movement, position + size);
    }
}

#include <iostream>

float FixAmount(const Math::Projection2 a, const Math::Projection2 b, const float movement)
{
    if(b.second <= a.first || a.second <= b.first)
    {
        return 0;
    }

    float left = b.first - a.second;  // negative
    float right = b.second - a.first; // positive

    if (movement == 0.0) {
        return fabs(left) <= fabs(right) ? left : right;
    } else if (0 < movement) {
        return left;
    } else {
        return right;
    }
}

void CollisionComponent::UpdateSnapshot()
{
    _positionSnapshot = _dim.Position;
}

bool CollisionComponent::Collides(const CollisionComponent & otherComponent,
                                  Point & fixNormal,
                                  float & fixMagnitude) const
{

    /**
     * The fixNormal and fixMagnitude are orientated such that 
     * this will push itself out of otherComponent.
     */
    sf::Vector2f movement = this->movement();
    auto thisX = Projection(_dim.Dimension.x, movement.x, _dim.Position.x);
    auto thisY = Projection(_dim.Dimension.y, movement.y, _dim.Position.y);
    
    auto otherMovement = otherComponent.movement();
    auto otherX = Projection(otherComponent._dim.Dimension.x,
                             otherMovement.x,
                             otherComponent._dim.Position.x);
    auto otherY = Projection(otherComponent._dim.Dimension.y,
                             otherMovement.y,
                             otherComponent._dim.Position.y);

    auto relativeMovement = movement - otherMovement;
    auto fixX = FixAmount(thisX, otherX, relativeMovement.x);
    auto fixY = FixAmount(thisY, otherY, relativeMovement.y);

    if (!_enabled || !otherComponent.enabled() || fixX == 0.0 || fixY == 0.0) {
        fixNormal = Point();
        fixMagnitude = 0;
        return false;
    }

    /*
     * When determining which fix is smaller, we compare relative to the 
     * absolute movement of the two components. That avoids the problem where
     * a component that falls onto another component gets pushed out the side
     * because it was pushed so far into the component.
     */
    if (fabs(fixX / relativeMovement.x) < fabs(fixY / relativeMovement.y)) {
        fixNormal = Point(Math::signum(fixX), 0);
        fixMagnitude = fabs(fixX);
        return true;
    } else {
        fixNormal = Point(0, Math::signum(fixY));
        fixMagnitude = fabs(fixY);
        return true;
    }
}

void CollisionComponent::UpdateDimensionPosition()
{
    auto & pos = _position->position();
    _dim.position(pos.x - (_dim.Dimension.x * _anchor.x), pos.y - (_dim.Dimension.y * _anchor.y));
}

std::vector<Collision> CollisionComponent::GetCollisions() const
{
    return GetCollisions(box());
}

std::vector<Collision> CollisionComponent::GetCollisions(const Box2 & box) const
{
    std::vector<Collision> collisions;
    if (!_enabled) {
        return collisions;
    }

    for (auto collision : _system->GetEntitiesInBox(box)) {
        if (collision.collisionComponent() != this) {
            collisions.push_back(collision);
        }
    }
    return collisions;
}

namespace ild {
template<>
struct Serializer<BodyTypeEnum> {
    static void Serialize(BodyTypeEnum & property, Archive & arc)
    {
        if (arc.loading())
        {
            const std::string & bodyTypeKey = arc.CurrentBranch().GetString();
            if(BodyTypeEnumStringMap.ContainsKey(bodyTypeKey))
            {
                property = BodyTypeEnumStringMap.GetValue(bodyTypeKey);
            }
            else
            {
                ILD_Assert(false, "Unknown body type");
            }
        }
        else
        {
            if(BodyTypeEnumStringMap.ContainsValue(property))
            {
                auto key = BodyTypeEnumStringMap.GetKey(property);
                arc.CurrentBranch().SetString(key.c_str(), key.length());
            }
            else
            {
                ILD_Assert(false, "Unknown body type");
            }
        }
    }

    static const rapidjson::Type SerializingType() 
    {
        return rapidjson::Type::kStringType;
    }
};
}

void CollisionComponent::Serialize(Archive &arc) {
    arc(_dim, "dimension");
    arc(_bodyType, "bodyType");
    arc(_anchor, "anchor");
    arc.system(_system, "collision");

    std::string key;
    if (!arc.loading())
    {
        key = _system->GetKeyFromType(_type);
    }

    arc(key, "collisionType");

    if (arc.loading())
    {
        _type = _system->GetType(key);
    }
}

void CollisionComponent::FetchDependencies(const Entity &entity) {
    _position = _system->position()[entity];
    UpdateDimensionPosition();
    UpdateSnapshot();
}
