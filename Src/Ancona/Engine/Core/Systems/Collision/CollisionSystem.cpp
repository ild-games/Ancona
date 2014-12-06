#include <Ancona/Engine/Core/Systems/Collision/CollisionSystem.hpp>
#include <Ancona/Util/Assert.hpp>

using namespace ild;

void nop(const Entity & e1,const Entity & e2) {}

CollisionSystem::CollisionSystem(SystemManager & manager, PositionSystem & positions)
    : UnorderedSystem<CollisionComponent>(manager,UpdateStep::Update), _positions(positions)
{
    _nextType = 0;

}

void CollisionSystem::Update(float delta)
{
    for(EntityComponentPair pair : * this)
    {
        pair.second->Update();
    }

}

CollisionComponent * CollisionSystem::CreateComponent(const Entity & entity,
        const sf::Vector3f & dim,
        const CollisionType type)
{
    Assert(type < _nextType, "Cannot use a collision type that is undefined");
    auto position = _positions[entity];
    auto component = new CollisionComponent(*position, dim, type);

    AttachComponent(entity, component);

    return component;
}

CollisionType CollisionSystem::CreateType()
{
    CollisionType newType = _nextType++;

    for(auto & callbackList : _callbackTable)
    {
        callbackList.push_back(nop);
    }

    _callbackTable.push_back(std::vector<CollisionCallback>());

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
