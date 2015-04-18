#include <Ancona/Platformer/Physics/Actions.hpp>
#include <Ancona/Util/Algorithm/ContainerWrappers.hpp>

using namespace ild;

Actions::Actions(BasePhysicsSystem * physicsSystem) : _physicsSystem(physicsSystem)
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

void Actions::Serialize(Archive & arc)
{
    arc(_positionActions, "platform-position-actions");
    arc(_velocityActions, "platform-velocity-actions");
    arc(_affectedByGravity, "affected-by-gravity");
    arc.system(_physicsSystem, "physics");
}

void RemoveDoneActions(std::vector<VectorActionProxy> & actions)
{
    actions.erase(
            alg::remove_if(
                actions,
                [](VectorActionProxy & action) { return action->Done(); }
                ),
            actions.end()
            );
}

static Point TweenPosition(VectorAction & action, float beforeRatio,
        const Point & position)
{
    float afterRatio = action.GetTweenRatio();

    if(afterRatio == 1)
    {
        return action.GetValue();
    }

    return position + (afterRatio - beforeRatio) / (1 - beforeRatio) *
        (action.GetValue() - position);
}

void Actions::StopFall()
{
    _totalGravity = Point();
}

void Actions::ApplyGravity(Point &velocity, float delta)
{
    _totalGravity += delta * _physicsSystem->GetGravity();
    velocity += _totalGravity;
}

Point Actions::ApplyPositionActions(const Position & position, float delta)
{
    Point location = position.GetPosition();
    for(auto& action : _positionActions)
    {
        float beforeRatio = action->GetTweenRatio();
        action->Update(delta);
        location = TweenPosition(*action,beforeRatio,position.GetPosition());
    }
    return location;
}

Point Actions::ApplyVelocityActions(const Position & position, float delta)
{
    Point velocity;
    for(auto& action : _velocityActions)
    {
        float overflow = action->Update(delta);
        auto value = action->GetValue();

        if(action->GetRelativeToGround())
        {
            auto groundDirection = position.GetGroundDirection();
            value = value.x * Point(-groundDirection.y,groundDirection.x);
        }

        if(overflow > 0)
        {
            velocity += value * (1 - overflow / delta);
        }
        else
        {
            velocity += action->GetTweenRatio() * value;
        }
    }
    return velocity;
}

void Actions::Apply(Position & position, float delta)
{
    //Velocity actions apply additively
    Point velocity = ApplyVelocityActions(position,delta);

    if(position.IsOnGround())
    {
        StopFall();
    }
    else if(_affectedByGravity)
    {
        ApplyGravity(velocity, delta);
    }

    position.SetVelocity(velocity);

    //Only update the position from the velocity if there are no position actions in effect.
    if(_positionActions.size() == 0)
    {
        position.SetPosition(position.GetPosition() + delta * velocity);
    }

    //Only a single position action will effect the result
    position.SetPosition(ApplyPositionActions(position, delta));

    RemoveDoneActions(_velocityActions);
    RemoveDoneActions(_positionActions);
}
