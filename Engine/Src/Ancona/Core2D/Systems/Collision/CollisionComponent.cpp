#include <Ancona/Util/Algorithm.hpp>
#include <Ancona/Util/Math.hpp>
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
        BodyTypeEnum bodyType)
    : _system(collisionSystem), _dim(dim.x,dim.y), _type(type), _bodyType(bodyType)
{

}

bool CollisionComponent::Collides(const CollisionComponent & otherComponent, Point & fixNormal, float & fixMagnitude) const
{
    return _dim.Intersects(otherComponent._dim, fixNormal, fixMagnitude);
}

void CollisionComponent::Update()
{
    UpdateDimensionPosition();
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
}
