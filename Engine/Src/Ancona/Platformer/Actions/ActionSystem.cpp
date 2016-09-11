#include <Ancona/Platformer/Actions/ActionSystem.hpp>

REGISTER_POLYMORPHIC_SERIALIZER(ild::ActionComponent);

using namespace ild;

/* Component */
ActionComponent::ActionComponent(ActionSystem * actionSystem) :
    _actions(actionSystem->positionSystem()),
    _positionSystem(actionSystem->positionSystem())
{
}

void ActionComponent::Serialize(Archive & archive)
{
    archive.system(_positionSystem,"position");
    archive(_actions, "actions");
}

void ActionComponent::Update(float delta)
{
    _actions.Apply(*_position, delta);
}

void ActionComponent::FetchDependencies(const Entity & entity)
{
    _actions.position(_positionSystem);
    _position = _positionSystem->at(entity);
}

/* System */
ActionSystem::ActionSystem(
        std::string systemName,
        SystemManager & manager,
        PositionSystem * positionSystem) :
    UnorderedSystem<ActionComponent>(systemName, manager, UpdateStep::Update),
    _positionSystem(positionSystem)
{
}

void ActionSystem::Update(float delta)
{
    for(EntityComponentPair pair : *this)
    {
        pair.second->Update(delta);
    }
}

ActionComponent * ActionSystem::CreateComponent(const Entity & entity)
{
    ActionComponent * component = new ActionComponent(this);
    AttachComponent(entity, component);
    return component;
}
