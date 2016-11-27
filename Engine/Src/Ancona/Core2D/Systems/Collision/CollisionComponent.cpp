#include <Ancona/Core2D/Systems/Collision/CollisionComponent.hpp>
#include <Ancona/Core2D/Systems/Collision/CollisionSystem.hpp>

using namespace ild;

static DualMap<std::string, BodyTypeEnum> BodyTypeEnumStringMap {
        { "none", BodyType::None },
        { "solid", BodyType::Solid },
        { "environment", BodyType::Environment }
};

CollisionComponent::CollisionComponent(
        CollisionSystem * collisionSystem,
        const Box2 & dim,
        const sf::Vector2f & scale,
        CollisionType type,
        BodyTypeEnum bodyType) :
    _system(collisionSystem),
    _dim(dim),
    _scale(scale),
    _type(type),
    _bodyType(bodyType)
{

}

bool CollisionComponent::Collides(const CollisionComponent & otherComponent, Point & fixNormal, float & fixMagnitude)
{
    return box().Intersects(otherComponent.box(), fixNormal, fixMagnitude);
}

void CollisionComponent::Update()
{
    auto & pos = _position->position();
    _dim.position(pos.x, pos.y);
    _position->groundDirection(Point());
}

CollisionType CollisionComponent::type()
{
    return _type;
}

namespace ild {
template<>
struct Serializer<BodyTypeEnum> {
    static void Serialize(BodyTypeEnum & property, Archive & arc)
    {
        if (arc.loading())
        {
            const std::string & bodyTypeKey = arc.CurrentBranch().asString();
            if(BodyTypeEnumStringMap.ContainsKey(bodyTypeKey))
            {
                property = BodyTypeEnumStringMap.GetValue(bodyTypeKey);
            }
            else
            {
                Assert(false, "Unknown body type");
            }
        }
        else
        {
            if(BodyTypeEnumStringMap.ContainsValue(property))
            {
                arc.CurrentBranch() = BodyTypeEnumStringMap.GetKey(property);
            }
            else
            {
                Assert(false, "Unknown body type");
            }
        }
    }
};
}

void CollisionComponent::Serialize(Archive &arc) {
    arc(_dim, "dimension");
    arc(_scale, "scale");
    arc(_bodyType, "bodyType");
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
}


const Box2 CollisionComponent::box() const
{
    auto box = Box2(_dim.Position, _dim.Dimension, _dim.Rotation);
    box.Dimension.x * _scale.x;
    box.Dimension.y * _scale.y;
    return box;
}
