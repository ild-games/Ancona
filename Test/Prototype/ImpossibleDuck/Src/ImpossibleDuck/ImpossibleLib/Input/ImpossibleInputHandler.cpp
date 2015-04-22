#include <Ancona/Core2D/InputDevices/InputHandler.hpp>
#include "../Systems/ImpossibleGameSystems.hpp"
#include "ImpossibleInputHandler.hpp"

using namespace ild;

static Point directions []= {Point(0,-1),Point(1,0),Point(0,1),Point(-1,0),Point(0,0)};

void ImpossibleInputHandler::RegisterInputComponent(ImpossibleInputComponent * component)
{
    _playerComponent = component;
}

ImpossibleInputComponent::ImpossibleInputComponent(
        const Entity & player,
        ImpossibleGameSystems & systems,
        ImpossibleInputHandler & inputHandler) :
    InputControlComponent(inputHandler),
    _physics(*systems.physics()[player]),
    _systems(systems),
    _playerEntity(player)
{
    inputHandler.RegisterInputComponent(this);
    action = _physics.actions().CreateVelocityAction();
    action->duration(ActionDuration::PERSISTENT)
          ->tween(0.5);

    jumpAction = _physics.actions().CreateVelocityAction();
    jumpAction
        ->duration(ActionDuration::PERSISTENT);
}

void ImpossibleInputComponent::Jump()
{
    if(_physics.GetInfo().onGround())
    {
        jumpAction->value(240.0f * directions[UP]);
        _systems.drawable()[_playerEntity]->GetDrawable("player-jump-animation")->inactive(false);
        _systems.drawable()[_playerEntity]->GetDrawable("player-walk-animation")->inactive(true);
    }
}

void ImpossibleInputComponent::GoDirection(int direction)
{
    if(_physics.GetInfo().onGround() != _isOnGround)
    {
        _isOnGround = _physics.GetInfo().onGround();

        if(_isOnGround)
        {
            jumpAction->value(Point());
        }

        action->isRelativeToGround(_isOnGround);
        lastDir = NO_DIR;
    }

    Move(direction);
}

void ImpossibleInputComponent::Move(int direction)
{
    float speed = _isOnGround ? 100.0f : 50.0f;

    if(lastDir != direction)
    {
        if(direction == RIGHT || direction == LEFT)
        {

            action->ResetAge();
            action->value(directions[direction] * speed);
        }
        else
        {
            action->value(Point());
        }
        lastDir = direction;
    }
}
