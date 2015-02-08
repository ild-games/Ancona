#include <Ancona/Engine/Core/Systems/Physics/Actions.hpp>

using namespace ild;

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

    return (afterRatio - beforeRatio) / (1 - beforeRatio) * 
        (action.GetValue() - position);
}

void Actions::Apply(Position & position, float delta)
{
    Point velocity;
    for(auto& action : _velocityActions)
    {
        velocity += action->GetTweenRatio() * action->GetValue();
        action->Update(delta);
    }

    //Update the velocity and the position from the velocity
    position.SetVelocity(velocity);
    position.SetPosition(position.GetVelocity() + delta * velocity);

    for(auto& action : _positionActions)
    {
        float beforeRatio = action->GetTweenRatio();
        action->Update(delta);
        position.SetPosition(TweenPosition(*action,beforeRatio,position.GetPosition()));
    }

    RemoveDoneActions(_velocityActions);
    RemoveDoneActions(_positionActions);
}
