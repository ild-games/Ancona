#include <algorithm>

#include <Ancona/Core2D/Systems/Collision/CollisionSystem.hpp>
#include <Ancona/Util/Assert.hpp>
#include <Ancona/Util/Algorithm.hpp>
#include <Ancona/Util/Math.hpp>
#include <Ancona/Util2D/VectorMath.hpp>


using namespace ild;

void nop(const Entity & e1,const Entity & e2,const Point & fixNormal, float fixMagnitude) {}

CollisionSystem::CollisionSystem(const std::string & name, SystemManager & manager, PositionSystem & positions)
    : UnorderedSystem<CollisionComponent>(name, manager,UpdateStep::Physics), _positions(positions)
{
    _nextType = 0;

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


bool CollisionSystem::CollisionAllowed(EntityComponentPair & a, EntityComponentPair & b, const Point & finalNormal)
{
    // if this same collision wasn't legal last frame, it's still not legal
    bool lastCollisionLegal = true;
    if (_lastCollisions.find(a.first) != _lastCollisions.end() && _lastCollisions[a.first].find(b.first) != _lastCollisions[a.first].end())
    {
        lastCollisionLegal = _lastCollisions[a.first][b.first];
    }

    //If either has a body type of None then the collision should not effect the position.
    bool eitherAreNone =
        a.second->bodyType() == BodyType::None ||
        b.second->bodyType() == BodyType::None;

    //Environment entities do not effect each other's positions.
    bool bothAreEnvironment =
        a.second->bodyType() == BodyType::Environment &&
        b.second->bodyType() == BodyType::Environment;

    bool blockedOneWay = true;
    if (a.second->oneWayNormal() != Point() || b.second->oneWayNormal() != Point())
    {
        blockedOneWay =
            a.second->oneWayNormal() == finalNormal ||
            b.second->oneWayNormal() == finalNormal;
    }

    return
        lastCollisionLegal &&
        blockedOneWay &&
        !eitherAreNone &&
        !bothAreEnvironment;
}

void CollisionSystem::FixCollision(EntityComponentPair & a, EntityComponentPair & b, const Point & fixNormal, float fixMagnitude)
{
    auto typeA = a.second->bodyType();
    auto typeB = b.second->bodyType();
    Point correctFix = fixMagnitude * fixNormal;

    bool collisionAllowed = CollisionAllowed(a, b, fixNormal * (float)Math::signum(fixMagnitude));
    _currentCollisions[a.first][b.first] = collisionAllowed;

    if(!collisionAllowed)
    {
        return;
    }

    if(typeA == BodyType::Solid && typeB == BodyType::Environment)
    {
        PushFirstOutOfSecond(a.second, b.second, correctFix);
    }
    else if (typeA == BodyType::Environment && typeB == BodyType::Solid)
    {
        PushFirstOutOfSecond(b.second, a.second, -correctFix);
    }
    else if(typeA == BodyType::Solid && typeB == BodyType::Solid)
    {
        PushApart(a.second, b.second, correctFix);
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
    a->SetCollisionDimensionPosition();
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
        b->SetCollisionDimensionPosition();
    }
    else if(posB.velocity() == Point())
    {
        posA.position(posA.position() + correctFix);
        a->SetCollisionDimensionPosition();
    }
    else
    {
        posA.position(posA.position() + 0.5f * correctFix);
        posB.position(posB.position() + -0.5f * correctFix);
        a->SetCollisionDimensionPosition();
        b->SetCollisionDimensionPosition();
    }
}

void CollisionSystem::Update(float delta)
{
    UpdateGravityBounds();
    _currentCollisions.clear();

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
    _lastCollisions = _currentCollisions;
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

    FixCollision(pairA, pairB, fixNormal, fixMagnitude);

    if (EntitiesOverlapping(fixMagnitude) && _currentCollisions[pairA.first][pairB.first])
    {
        _callbackTable.Get(typeA, typeB)(pairA.first, pairB.first, fixNormal, fixMagnitude);
        _callbackTable.Get(typeB, typeA)(pairB.first, pairA.first, fixNormal, fixMagnitude);
    }

}

bool CollisionSystem::EntitiesOverlapping(float fixMagnitude)
{
    return fixMagnitude != 0;
}
