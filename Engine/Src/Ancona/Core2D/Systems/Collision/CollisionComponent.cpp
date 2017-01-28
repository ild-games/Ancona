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
    _dim.position(pos.x, pos.y);
}

CollisionType CollisionComponent::type()
{
    return _type;
}

std::vector<Collision> CollisionComponent::GetProjectionCollisions(ild::Point direction) const {
    std::vector<std::pair<Entity, CollisionComponent *>> collisions;

    if (direction.x != 0) {

        Box2 box = this->box();
        box.position(
            Math::signum(direction.x) * box.Dimension.x / 2 + box.Position.x + direction.x,
            direction.y + box.Position.y);
        box.dimension(direction.x, box.Dimension.y);
        for (auto collision : _system->GetEntitiesInBox(box)) {
            collisions.push_back(collision);
        }
    }

    if (direction.y != 0) {
        Box2 box = this->box();
        box.position(
            direction.x + box.Position.x,
            Math::signum(direction.y) * box.Dimension.y / 2 + box.Position.y + direction.y);
        box.dimension(box.Dimension.x, direction.y);
        for (auto collision : _system->GetEntitiesInBox(box)) {
            if (!alg::contains(collisions, collision)) {
                collisions.push_back(collision);
            }
        }
    }

    std::vector<Collision> result;
    for (auto collision : collisions) {
        result.emplace_back(collision.first, collision.second);
    }
    return result;
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
