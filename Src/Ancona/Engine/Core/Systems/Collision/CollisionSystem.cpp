#include <algorithm>

#include <Ancona/Engine/Core/Systems/Collision/CollisionSystem.hpp>
#include <Ancona/Util/Assert.hpp>
#include <Ancona/Util/VectorMath.hpp>

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

    if(typeA == BodyType::Environment && typeB == BodyType::Solid)
    {
        std::swap(a,b); 
        std::swap(typeA,typeB);
        correctFix = -correctFix;
    }

    if(typeA == BodyType::Solid && typeB == BodyType::Environment)
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

    if(typeA == BodyType::Solid && typeB == BodyType::Solid)
    {
        //If both bodies are solid then push them out of eachoter.
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

}

void CollisionSystem::Update(float delta)
{
    UpdateGravityBounds();

    //Update all of the entities.  This is required for the position to be up to date.
    for(EntityComponentPair pair : * this)
    {
        pair.second->Update();
    }

    for(EntityComponentPair pairA : * this)
    {
        for(EntityComponentPair pairB : * this)
        {
            //Only have each pair of entities collide once.
            if(pairA.first >= pairB.first)
            {
                continue;
            }

            Point fixNormal;
            float fixMagnitude;
            if(pairA.second->Collides(*pairB.second, fixNormal, fixMagnitude))
            {
                auto typeA = pairA.second->GetType();
                auto typeB = pairB.second->GetType();

                FixCollision(pairA.second, pairB.second, fixNormal, fixMagnitude);

                //If the objects are adjacent, but not overlapping then the collision handlers should
                //not be called.
                if(fixMagnitude != 0)
                {
                    _callbackTable[typeA][typeB](pairA.first, pairB.first);
                    _callbackTable[typeB][typeA](pairB.first, pairA.first);
                }
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
    CollisionType newType = _nextType++;

    //Add slot for new collision type to the existing vectors.
    for(auto & callbackList : _callbackTable)
    {
        callbackList.push_back(nop);
    }

    _callbackTable.push_back(std::vector<CollisionCallback>());

    //Create the vector for the new collision type.
    auto & back = _callbackTable.back();
    for(int i = 0; i < _nextType; i++)
    {
        back.push_back(nop);
    }

    _collisionTypes.emplace(key, newType);

    return newType;
}

void CollisionSystem::SetHandler(CollisionType typeA, CollisionType typeB, CollisionCallback callback)
{
    Assert(typeA < _nextType, "The given typeA does not exist");
    Assert(typeB < _nextType, "The given typeB does not exist");

    _callbackTable[typeA][typeB] = callback;
}

CollisionType CollisionSystem::GetType(const std::string &key) {
    Assert(_collisionTypes.find(key) != _collisionTypes.end(), "The collision type must exist");

    return _collisionTypes[key];
}
