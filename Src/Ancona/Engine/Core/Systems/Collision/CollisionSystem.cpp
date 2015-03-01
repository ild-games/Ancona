#include <algorithm>

#include <Ancona/Engine/Core/Systems/Collision/CollisionSystem.hpp>
#include <Ancona/Util/Assert.hpp>

using namespace ild;

void nop(const Entity & e1,const Entity & e2) {}

CollisionSystem::CollisionSystem(SystemManager & manager, BasePhysicsSystem & positions)
    : UnorderedSystem<CollisionComponent>(manager,UpdateStep::Update), _positions(positions)
{
    _nextType = 0;

}

static void FixCollision(CollisionComponent * a, CollisionComponent * b, const Point & fix)
{
    auto typeA = a->GetBodyType();
    auto typeB = b->GetBodyType();
    Point correctFix = fix;

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
        posA.SetPosition(posA.GetPosition() + correctFix);
        return;
    }

    if(typeA == BodyType::Solid && typeB == BodyType::Solid)
    {
        //If both bodies are solid then push them out of eachoter.
        auto & physicsA = a->GetPhysicsComponent();
        auto & posA = physicsA.GetMutableInfo();
        auto & physicsB = b->GetPhysicsComponent();
        auto & posB = physicsB.GetMutableInfo();

        if(posA.GetVelocity() == Point())
        {
            posB.SetPosition(posB.GetPosition() + -correctFix);
        } 
        else if(posB.GetVelocity() == Point())
        {
            posA.SetPosition(posA.GetPosition() + correctFix);
        }
        else
        {
            posA.SetPosition(posA.GetPosition() + 0.5f * correctFix);
            posB.SetPosition(posB.GetPosition() + -0.5f * correctFix);
        }

        return;
    }

}

void CollisionSystem::Update(float delta)
{
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
            if(pairA.first > pairB.first)
            {
                continue;
            }

            Point fix;
            if(pairA.second->Collides(*pairB.second, fix))
            {
                auto typeA = pairA.second->GetType();
                auto typeB = pairB.second->GetType();

                FixCollision(pairA.second, pairB.second, fix);

                _callbackTable[typeA][typeB](pairA.first, pairB.first);
                _callbackTable[typeB][typeA](pairB.first, pairA.first);
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
    auto position = _positions[entity];
    auto component = new CollisionComponent(*position, dim, type, bodyType);

    AttachComponent(entity, component);

    return component;
}

CollisionType CollisionSystem::CreateType()
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
    
    return newType;
}

void CollisionSystem::SetHandler(CollisionType typeA, CollisionType typeB, CollisionCallback callback)
{
    Assert(typeA < _nextType, "The given typeA does not exist");
    Assert(typeB < _nextType, "The given typeB does not exist");

    _callbackTable[typeA][typeB] = callback;
}
