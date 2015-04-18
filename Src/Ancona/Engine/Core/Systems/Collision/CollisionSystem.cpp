#include <algorithm>

#include <Ancona/Engine/Core/Systems/Collision/CollisionSystem.hpp>
#include <Ancona/Util/Assert.hpp>
#include <Ancona/Util/Algorithm.hpp>
#include <Ancona/Util2D/VectorMath.hpp>

using namespace ild;

void nop(const Entity & e1,const Entity & e2) {}

CollisionSystem::CollisionSystem(const std::string & name, SystemManager & manager, BasePhysicsSystem & positions)
    : UnorderedSystem<CollisionComponent>(name, manager,UpdateStep::Update), _positions(positions)
{
    _nextType = 0;

}

void CollisionSystem::UpdateGravityBounds()
{
    auto invGravity =  -_positions.GetGravity();
    
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
    auto typeA = a->GetBodyType();
    auto typeB = b->GetBodyType();
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
    if(typeA == BodyType::Solid && typeB == BodyType::Solid)
    {
        PushApart(a, b, correctFix);
    }

}

void CollisionSystem::PushFirstOutOfSecond(CollisionComponent *a, CollisionComponent *b, const Point &correctFix)
{
    auto & physicsA = a->GetPhysicsComponent();
    auto & posA = physicsA.GetMutableInfo();

    auto groundDirection = VectorMath::Normalize(b->GetBox().GetNormalOfCollisionEdge(a->GetBox()));
    if(IsOnGround(groundDirection))
        {
            posA.SetGroundDirection(groundDirection);
        }

    posA.SetPosition(posA.GetPosition() + correctFix);
    return;
}

void CollisionSystem::PushApart(CollisionComponent *a, CollisionComponent *b, const Point &correctFix)
{//If both bodies are solid then push them out of eachoter.
    auto & physicsA = a->GetPhysicsComponent();
    auto & infoA = physicsA.GetMutableInfo();
    auto & physicsB = b->GetPhysicsComponent();
    auto & infoB = physicsB.GetMutableInfo();

    if(infoA.GetVelocity() == Point())
        {
            infoB.SetPosition(infoB.GetPosition() + -correctFix);
        }
        else if(infoB.GetVelocity() == Point())
        {
            infoA.SetPosition(infoA.GetPosition() + correctFix);
        }
        else
        {
            infoA.SetPosition(infoA.GetPosition() + 0.5f * correctFix);
            infoB.SetPosition(infoB.GetPosition() + -0.5f * correctFix);
        }

    return;
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

    return newType;
}

void CollisionSystem::DefineCollisionCallback(CollisionType typeA, CollisionType typeB, CollisionCallback callback)
{
    Assert(typeA < _nextType, "The given typeA does not exist");
    Assert(typeB < _nextType, "The given typeB does not exist");

    _callbackTable.Get(typeA, typeB) = callback;
}

CollisionType CollisionSystem::GetType(const std::string &key) {
    Assert(IsCollisionTypeDefined(key), "The collision type must exist");

    return _collisionTypes[key];
}

bool CollisionSystem::IsCollisionTypeDefined(std::string const &key)
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
    auto typeA = pairA.second->GetType();
    auto typeB = pairB.second->GetType();

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
