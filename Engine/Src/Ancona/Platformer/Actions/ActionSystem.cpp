#include <Ancona/Platformer/Actions/ActionSystem.hpp>

REGISTER_POLYMORPHIC_SERIALIZER(ild::ActionComponent);

using namespace ild;

/* Component */
ActionComponent::ActionComponent(ActionSystem *actionSystem)
    : _actions(actionSystem->positionSystem(), actionSystem->drawableSystem()),
      _positionSystem(actionSystem->positionSystem()), _drawableSystem(actionSystem->drawableSystem())
{
}

void ActionComponent::Serialize(Archive &archive)
{
    archive.system(_positionSystem, "position");
    archive.system(_drawableSystem, "drawable");
    archive(_actions, "actions");
}

void ActionComponent::Update(float delta)
{
    _actions.Apply(*_position, *_drawable, delta);
}

void ActionComponent::FetchDependencies(const Entity &entity)
{
    _actions.position(_positionSystem);
    _position = _positionSystem->at(entity);
    _drawable = _drawableSystem->at(entity);
}

/* System */
ActionSystem::ActionSystem(std::string systemName, SystemManager &manager, PositionSystem *positionSystem,
                           DrawableSystem *drawableSystem)
    : UnorderedSystem<ActionComponent>(systemName, manager, UpdateStep::Update), _positionSystem(positionSystem),
      _drawableSystem(drawableSystem)
{
}

void ActionSystem::Update(float delta)
{
    for (EntityComponentPair pair : *this)
    {
        pair.second->Update(delta);
    }
}

ActionComponent *ActionSystem::CreateComponent(const Entity &entity)
{
    ActionComponent *component = new ActionComponent(this);
    AttachComponent(entity, component);
    return component;
}
