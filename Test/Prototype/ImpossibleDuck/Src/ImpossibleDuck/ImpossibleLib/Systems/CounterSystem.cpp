#include "CounterSystem.hpp"

using namespace ild;

/* Component */
CounterComponent::CounterComponent() : 
    _counter(0),
    _countInterval(1)
{ 
} 

CounterComponent::CounterComponent(
        int startingNumber,
        int countInterval) : 
    _counter(startingNumber),
    _countInterval(countInterval)
{
}

void CounterComponent::AddCounter()
{
    _counter += _countInterval;
}

void CounterComponent::FetchDependencies(const Entity & entity)
{
     
}

void CounterComponent::Serialize(Archive & arc)
{
    arc(_counter, "count");
    arc(_countInterval, "count-interval");
}

/* System */
CounterSystem::CounterSystem(
        std::string name,
        SystemManager & manager) :
    UnorderedSystem(name, manager, UpdateStep::Update)
{
}

void CounterSystem::Update(float delta)
{
    //no-op
}

CounterComponent * CounterSystem::CreateComponent(
        const Entity & entity,
        int startingNumber,
        int countInterval)
{
    CounterComponent * comp = new CounterComponent(
            startingNumber,
            countInterval);
    AttachComponent(entity, comp);
    return comp;
}
