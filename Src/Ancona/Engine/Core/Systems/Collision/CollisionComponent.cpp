#include <Ancona/Engine/Core/Systems/Collision/CollisionComponent.hpp>
#include <Ancona/Engine/Core/Systems/Collision/CollisionSystem.hpp>

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
    auto & pos = info.GetPosition();
    _dim.SetPosition(pos.x, pos.y);
    info.SetGroundDirection(Point());
}

CollisionType CollisionComponent::GetType()
{
    return _type;
}

namespace ild {
template<>
struct Serializer<BodyTypeEnum> {
    static void Serialize(BodyTypeEnum & property, Archive & arc)
    {
        if (arc.IsLoading())
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
                Assert(false, "Unkown body type");
            }
        }
        else
        {
            //TODO ANC-77 implement BodyTypeEnum saving
        }
    }
};
}

void CollisionComponent::Serialize(Archive &arc) {
    arc(_dim, "dimension");
    arc(_bodyType, "body-type");
    arc.system(_system, "collision");

    std::string key;
    if (!arc.IsLoading())
    {
        //TODO ANC-77 implement CollisionComponent saving
    }

    arc(key, "collision-type");

    if (arc.IsLoading())
    {
        _type = _system->GetType(key);
    }
}

void CollisionComponent::FetchDependencies(const Entity &entity) {
    _position = _system->GetPhysics()[entity];
}
