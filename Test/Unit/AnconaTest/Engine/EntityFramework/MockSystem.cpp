#include <algorithm>

#include "MockSystem.hpp"

using namespace ild;

MockComponent::MockComponent()
{
    _wasUpdated = false;
}

bool MockComponent::WasUpdated()
{
    return _wasUpdated;
}

void MockComponent::ClearUpdate()
{
    _wasUpdated = false;
}

void MockComponent::Update()
{
    _wasUpdated = true;
}

MockSystem::MockSystem(SystemManager & manager) :
    UnorderedSystem(manager, UpdateStepEnum::Update)
{
    ComponentRemoved = false;
}

void MockSystem::Update(float delta)
{
    for(EntityComponentPair component : *this)
    {
        component.second->Update(); 
    }
}

MockComponent * MockSystem::CreateComponent(const Entity & entity)
{
    auto comp = new MockComponent();
    AttachComponent(entity, comp);
    return comp;
}

int MockSystem::ComponentCount()
{
    return std::distance(begin(), end());
}

void MockSystem::OnComponentRemove(Entity entity, MockComponent * component)
{
    ComponentRemoved = true;
}
