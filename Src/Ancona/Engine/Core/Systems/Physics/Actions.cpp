#include <Ancona/Engine/Core/Systems/Physics/Actions.hpp>

using namespace ild;

Actions::Actions(BasePhysicsSystem & physicsSystem) : _physicsSystem(physicsSystem)
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

void RemoveDoneActions(std::vector<VectorActionProxy> & actions)
{
    actions.erase(
            std::remove_if(
                actions.begin(), actions.end(),
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
    _totalGravity += delta * _physicsSystem.GetGravity();
    velocity += _totalGravity;
}

void Actions::Apply(Position & position, float delta)
{
    Point velocity;
    for(auto& action : _velocityActions)
    {
        float overflow = action->Update(delta);
        if(overflow > 0)
        {
            velocity += action->GetValue() * (1 - overflow / delta);
        }
        else
        {
            velocity += action->GetTweenRatio() * action->GetValue();
        }
    }

    if(position.IsOnGround())
    {
        StopFall();
    }
    else if(_effectedByGravity)
    {
        ApplyGravity(velocity, delta);
    }

    position.SetVelocity(velocity);

    //Only update the position from the velocity if there are no position actions in effect.
    if(_positionActions.size() == 0)
    {
        position.SetPosition(position.GetPosition() + delta * velocity);
    }

    for(auto& action : _positionActions)
    {
        float beforeRatio = action->GetTweenRatio();
        action->Update(delta);
        position.SetPosition(TweenPosition(*action,beforeRatio,position.GetPosition()));
    }

    RemoveDoneActions(_velocityActions);
    RemoveDoneActions(_positionActions);
}
