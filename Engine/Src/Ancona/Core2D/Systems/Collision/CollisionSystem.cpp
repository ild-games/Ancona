#include <algorithm>
#include <json/json.h>

#include <Ancona/Core2D/Systems/Collision/CollisionSystem.hpp>
#include <Ancona/Util/Assert.hpp>
#include <Ancona/Util/Algorithm.hpp>
#include <Ancona/Util2D/VectorMath.hpp>
#include <Ancona/System/FileOperations.hpp>

using namespace ild;

void nop(const Entity & e1,const Entity & e2) {}

CollisionSystem::CollisionSystem(const std::string & name, SystemManager & manager, PositionSystem & positions)
    : UnorderedSystem<CollisionComponent>(name, manager,UpdateStep::Physics), _positions(positions)
{
    _nextType = 0;

}

void CollisionSystem::OnLoad()
{
    CreateType(NONE_COLLISION_TYPE);
    if (FileOperations::IsFile("project/collision-types.json"))
    {
        auto fileStream = FileOperations::GetInputFileStream("project/collision-types.json");
        Json::Reader reader;
        Json::Value collisionTypesRoot;
        reader.parse(*fileStream, collisionTypesRoot);
        for (Json::Value & collisionType : collisionTypesRoot["collisionTypes"])
        {
            if (collisionType.asString() != NONE_COLLISION_TYPE) 
            {
                CreateType(collisionType.asString());
            }
        }
    }
}

void CollisionSystem::UpdateGravityBounds()
{
    auto invGravity =  -_positions.gravity();

    _leftGravityBound = VectorMath::Rotate(invGravity, VectorMath::DegreesToRadians(90 - _maxSlope));
    _rightGravityBound = VectorMath::Rotate(invGravity, VectorMath::DegreesToRadians(-(90 - _maxSlope)));
}

bool CollisionSystem::IsOnGround(const Point &groundNormal)
{
    if(groundNormal != Point())
    {
        return VectorMath::Between(_leftGravityBound, _rightGravityBound, groundNormal);
    }
    return false;
}

void CollisionSystem::FixCollision(CollisionComponent * a, CollisionComponent * b, const Point & fixNormal, float fixMagnitude)
{
    auto typeA = a->bodyType();
    auto typeB = b->bodyType();
    Point correctFix = fixMagnitude * fixNormal;

    //If either has a body type of None then the collision should not effect the position.
    if(typeA == BodyType::None || typeB == BodyType::None)
    {
        return;
    }

    //Environment entities do not effect each other's positions.
    if(typeA == BodyType::Environment && typeB == BodyType::Environment)
    {
        return;
    }

    if(typeA == BodyType::Solid && typeB == BodyType::Environment)
    {
        PushFirstOutOfSecond(a, b, correctFix);
    }
    else if (typeA == BodyType::Environment && typeB == BodyType::Solid)
    {
        PushFirstOutOfSecond(b, a, -correctFix);
    }
    else if(typeA == BodyType::Solid && typeB == BodyType::Solid)
    {
        PushApart(a, b, correctFix);
    }

}

void CollisionSystem::PushFirstOutOfSecond(CollisionComponent *a, CollisionComponent *b, const Point &correctFix)
{
    auto & posA = a->positionComponent();

    auto groundDirection = VectorMath::Normalize(b->box().GetNormalOfCollisionEdge(a->box()));
    if(IsOnGround(groundDirection))
    {
        posA.groundDirection(groundDirection);
    }

    posA.position(posA.position() + correctFix);
    return;
}

void CollisionSystem::PushApart(CollisionComponent *a, CollisionComponent *b, const Point &correctFix)
{
    //If both bodies are solid then push them out of eachoter.
    auto & posA = a->positionComponent();
    auto & posB = b->positionComponent();

    if(posA.velocity() == Point())
    {
        posB.position(posB.position() + -correctFix);
    }
    else if(posB.velocity() == Point())
    {
        posA.position(posA.position() + correctFix);
    }
    else
    {
        posA.position(posA.position() + 0.5f * correctFix);
        posB.position(posB.position() + -0.5f * correctFix);
    }
}

void CollisionSystem::Update(float delta)
{
    UpdateGravityBounds();

    //Update all of the entities.  This is required for the position to be up to date.
    for(EntityComponentPair pair : * this)
    {
        pair.second->Update();
    }

    for(EntityComponentPair entityComponentPairA : * this)
    {
        for(EntityComponentPair entityComponentPairB : * this)
        {
            if(!UniqueCollision(entityComponentPairA.first, entityComponentPairB.first))
            {
                continue;
            }

            Point fixNormal;
            float fixMagnitude;
            if(entityComponentPairA.second->Collides(*entityComponentPairB.second, fixNormal, fixMagnitude))
            {
                HandleCollision(entityComponentPairA,entityComponentPairB,fixNormal,fixMagnitude);
            }
        }
    }

}

CollisionComponent * CollisionSystem::CreateComponent(const Entity & entity,
        const sf::Vector3f & dim,
        CollisionType type,
        BodyTypeEnum bodyType)
{
    Assert(type < _nextType, "Cannot use a collision type that is undefined");
    auto component = new CollisionComponent(this, dim, type, bodyType);

    AttachComponent(entity, component);

    return component;
}

CollisionType CollisionSystem::CreateType(const std::string &key)
{
    Assert(!IsCollisionTypeDefined(key), "The same key cannot be used to define two collision types");

    CollisionType newType = _nextType++;
    _callbackTable.AddColumn(nop);
    _callbackTable.AddRow(nop);
    _collisionTypes.emplace(key, newType);
    _collisionTypeToKey.emplace(newType, key);

    return newType;
}

void CollisionSystem::DefineCollisionCallback(CollisionType typeA, CollisionType typeB, CollisionCallback callback)
{
    Assert(typeA < _nextType, "The given typeA does not exist");
    Assert(typeB < _nextType, "The given typeB does not exist");

    _callbackTable.Get(typeA, typeB) = callback;
}

CollisionType CollisionSystem::GetType(const std::string &key)
{
    Assert(IsCollisionTypeDefined(key), "The collision type must exist");

    return _collisionTypes[key];
}

std::string CollisionSystem::GetKeyFromType(const CollisionType & type)
{
    return _collisionTypeToKey[type];
}

bool CollisionSystem::IsCollisionTypeDefined(const std::string & key)
{
    return _collisionTypes.find(key) != _collisionTypes.end();
}

bool CollisionSystem::UniqueCollision(const Entity &entityA, const Entity &entityB)
{
    return entityA < entityB;
}

void CollisionSystem::HandleCollision(
        EntityComponentPair &pairA, EntityComponentPair &pairB,
        const Point &fixNormal, float fixMagnitude)
{
    auto typeA = pairA.second->type();
    auto typeB = pairB.second->type();

    FixCollision(pairA.second, pairB.second, fixNormal, fixMagnitude);

    if(EntitiesOverlapping(fixMagnitude))
    {
        _callbackTable.Get(typeA, typeB)(pairA.first, pairB.first);
        _callbackTable.Get(typeB, typeA)(pairB.first, pairA.first);
    }
}

bool CollisionSystem::EntitiesOverlapping(float fixMagnitude)
{
    return fixMagnitude != 0;
}
