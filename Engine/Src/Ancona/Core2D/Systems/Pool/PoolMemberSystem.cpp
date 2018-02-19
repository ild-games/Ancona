#include "PoolMemberSystem.hpp"

using namespace ild;

////////// TEMPLATIZED SYSTEM SETUP INSTRUCTIONS
/// Before using this you must initialize an instance of the template in your GameSystems class

/* Component */
PoolMemberComponent::PoolMemberComponent()
{
}

void PoolMemberComponent::Update(float delta)
{
    // Implement component logic here
}

void PoolMemberComponent::Serialize(Archive & arc)
{
    // Implement component serialization here
}

void PoolMemberComponent::FetchDependencies(const Entity &entity)
{
    // Implement component post serialization dependency fetch here
}

/* System */
PoolMemberSystem::PoolMemberSystem(
        std::string name,
        SystemManager &manager) :
    UnorderedSystem(name, manager, UpdateStep::Update)
{
}

void PoolMemberSystem::Update(float delta)
{
    for (EntityComponentPair comp : *this)
    {
        comp.second->Update(delta);
    }
}

PoolMemberComponent * PoolMemberSystem::CreateComponent(const Entity &entity)
{
    PoolMemberComponent * comp = new PoolMemberComponent();
    AttachComponent(entity, comp);
    return comp;
}
