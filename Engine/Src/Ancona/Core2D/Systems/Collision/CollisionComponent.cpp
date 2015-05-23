#include <Ancona/Core2D/Systems/Collision/CollisionComponent.hpp>
#include <Ancona/Core2D/Systems/Collision/CollisionSystem.hpp>

using namespace ild;

CollisionComponent::CollisionComponent(CollisionSystem * collisionSystem,
        const sf::Vector3f & dim,
        CollisionType type,
        BodyTypeEnum bodyType)
    : _system(collisionSystem), _dim(dim.x,dim.y), _type(type), _bodyType(bodyType)
{
    
}

bool CollisionComponent::Collides(const CollisionComponent & otherComponent, Point & fixNormal, float & fixMagnitude)
{
    return _dim.Intersects(otherComponent._dim, fixNormal, fixMagnitude);
}

void CollisionComponent::Update()
{
    auto & info = _position->GetMutableInfo();
    auto & pos = info.position();
    _dim.position(pos.x, pos.y);
    info.groundDirection(Point());
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
            const std::string & val = arc.CurrentBranch().asString();
            if (val == "none")
            {
                property = BodyType::None;
            }
            else if (val == "solid")
            {
                property = BodyType::Solid;
            }
            else if (val == "environment")
            {
                property = BodyType::Environment;
            }
            else
            {
                Assert(false, "Unknown body type");
            }
        }
        else
        {
            if(property == BodyType::None)
            {
                arc.CurrentBranch() = "none";
            }
            else if(property == BodyType::Solid)
            {
                arc.CurrentBranch() = "solid";
            }
            else if(property == BodyType::Environment)
            {
                arc.CurrentBranch() = "environment";
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
    arc(_bodyType, "body-type");
    arc.system(_system, "collision");

    std::string key;
    if (!arc.loading())
    {
        key = _system->GetKeyFromType(_type);
    }

    arc(key, "collision-type");

    if (arc.loading())
    {
        _type = _system->GetType(key);
    }
}

void CollisionComponent::FetchDependencies(const Entity &entity) {
    _position = _system->physics()[entity];
}
