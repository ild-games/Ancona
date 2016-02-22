#include <Ancona/Platformer/Actions/Actions.hpp>
#include <Ancona/Util/Algorithm/ContainerWrappers.hpp>

using namespace ild;

Actions::Actions(PositionSystem * positionSystem) : _positionSystem(positionSystem)
{
}

VectorActionProxy Actions::CreatePositionAction()
{
    VectorActionProxy action(new VectorAction());

    _positionActions.push_back(action);

    return action;
}

VectorActionProxy Actions::CreateVelocityAction()
{
    VectorActionProxy action(new VectorAction());

    _velocityActions.push_back(action);


    return action;
}

JumpActionProxy Actions::CreateJumpAction()
{
    auto jumpVelocityAction = CreateVelocityAction();
    jumpVelocityAction->duration(ActionDuration::PERSISTENT);

    JumpActionProxy action(new JumpAction());
    action->velocityAction(jumpVelocityAction);
    _jumpActions.push_back(action);

    return action;
}

void Actions::Serialize(Archive & arc)
{
    arc(_velocityActions, "platformVelocityActions");
    arc(_positionActions, "platformPositionActions");
    arc(_jumpActions, "platformPositionActions");
    arc(_affectedByGravity, "affectedByGravity");
    arc.system(_positionSystem, "position");
}


static Point TweenPosition(VectorAction & action, float beforeRatio,
        const Point & position)
{
    float afterRatio = action.tweenRatio();

    if(afterRatio == 1)
    {
        return action.value();
    }

    return position + (afterRatio - beforeRatio) / (1 - beforeRatio) *
        (action.value() - position);
}

void Actions::StopFall()
{
    _totalGravity = Point();
}

void Actions::ApplyGravity(Point &velocity, float delta)
{
    _totalGravity += delta * _positionSystem->gravity();
    velocity += _totalGravity;
}

Point Actions::ApplyPositionActions(const PositionComponent & position, float delta)
{
    Point location = position.position();
    for(auto& action : _positionActions)
    {
        float beforeRatio = action->tweenRatio();
        action->Update(delta);
        location = TweenPosition(*action, beforeRatio, position.position());
    }
    return location;
}

Point Actions::ApplyVelocityActions(const PositionComponent & position, float delta)
{
    Point velocity;
    for(auto& action : _velocityActions)
    {
        float overflow = action->Update(delta);
        auto value = action->value();

        if(action->isRelativeToGround())
        {
            auto groundDirection = position.groundDirection();
            value = value.x * Point(-groundDirection.y,groundDirection.x);
        }

        if(overflow > 0)
        {
            velocity += value * (1 - overflow / delta);
        }
        else
        {
            velocity += action->tweenRatio() * value;
        }
    }
    return velocity;
}

void Actions::ApplyJumpActions()
{
    for (auto & jumpAction : _jumpActions)
    {
        jumpAction->ApplyJumpEvents(_totalGravity);
    }
}

void Actions::Apply(PositionComponent & position, float delta)
{
    ApplyJumpActions();

    //Velocity actions apply additively
    Point velocity = ApplyVelocityActions(position,delta);

    //ApplyGravity(velocity, delta);
    if(position.onGround())
    {
        StopFall();
    }
    else if(_affectedByGravity)
    {
        ApplyGravity(velocity, delta);
    }

    if (_positionActions.size())
    {
        //Only a single position action will effect the result
        position.position(ApplyPositionActions(position, delta));
        position.velocity(Point());
    }
    else
    {
        auto diff = velocity - _actionVelocity;
        position.velocity(position.velocity() + diff);
        _actionVelocity = velocity;
    }

    RemoveDoneActions<VectorActionProxy>(_velocityActions);
    RemoveDoneActions<VectorActionProxy>(_positionActions);
    RemoveDoneActions<JumpActionProxy>(_jumpActions);
}
