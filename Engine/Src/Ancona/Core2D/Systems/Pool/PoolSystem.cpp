#include "PoolSystem.hpp"

using namespace ild;

////////// TEMPLATIZED SYSTEM SETUP INSTRUCTIONS
/// Before using this you must initialize an instance of the template in your GameSystems class

/* Component */
PoolComponent::PoolComponent()
{
}

void PoolComponent::Update(float delta)
{
    // Implement component logic here
}

void PoolComponent::Serialize(Archive & arc)
{
    // Implement component serialization here
}

void PoolComponent::FetchDependencies(const Entity &entity)
{
    // Implement component post serialization dependency fetch here
}

/* System */
PoolSystem::PoolSystem(
        std::string name,
        SystemManager &manager) :
    UnorderedSystem(name, manager, UpdateStep::Update)
{
}

void PoolSystem::Update(float delta)
{
}

PoolComponent * PoolSystem::CreateComponent(const Entity &entity)
{
    PoolComponent * comp = new PoolComponent();
    AttachComponent(entity, comp);
    return comp;
}
