#include "TriggerDeathSystem.hpp"

namespace ild
{

/* Component */
TriggerDeathComponent::TriggerDeathComponent()
{
}

void TriggerDeathComponent::Update(float delta)
{
    if (_animation->IsFinished())
    {
        _systemManager->QueueDeleteEntity(_entity);
    }
}

void TriggerDeathComponent::Serialize(Archive & arc)
{
    arc(_animationToWatch, "animationToWatch");
    arc.system(_drawableSystem, "drawable");
    arc.systemManager(_systemManager);
}

void TriggerDeathComponent::FetchDependencies(const Entity & entity)
{
    _animation =
        static_cast<AnimatedDrawable *>(_drawableSystem->at(entity)->topDrawable()->FindDrawable(_animationToWatch));
    _entity = entity;
}

/* System */
TriggerDeathSystem::TriggerDeathSystem(std::string name, SystemManager & manager) :
        UnorderedSystem(name, manager, UpdateStep::Update)
{
}

void TriggerDeathSystem::Update(float delta)
{
    for (EntityComponentPair comp : *this)
    {
        comp.second->Update(delta);
    }
}

TriggerDeathComponent * TriggerDeathSystem::CreateComponent(const Entity & entity)
{
    TriggerDeathComponent * comp = new TriggerDeathComponent();
    AttachComponent(entity, comp);
    return comp;
}

} // namespace ild
