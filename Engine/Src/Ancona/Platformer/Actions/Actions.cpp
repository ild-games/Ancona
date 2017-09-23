#include <Ancona/Platformer/Actions/Actions.hpp>
#include <Ancona/Util/Algorithm/ContainerWrappers.hpp>
#include <Ancona/System/Log.hpp>

using namespace ild;

Actions::Actions(
        PositionSystem * positionSystem,
        DrawableSystem * drawableSystem) : 
    _positionSystem(positionSystem),
    _drawableSystem(drawableSystem)
{
}

VectorActionProxy Actions::CreatePositionAction()
{
    VectorActionProxy action(new ValueAction<sf::Vector2f>());
    _positionActions.push_back(action);
    return action;
}

VectorActionProxy Actions::CreateVelocityAction()
{
    VectorActionProxy action(new ValueAction<sf::Vector2f>());
    _velocityActions.push_back(action);
    return action;
}

VectorActionProxy Actions::CreateScaleAction(std::string drawableKey)
{
    ScaleActionProxy action(new ScaleAction<sf::Vector2f>(drawableKey));
    _scaleActions.push_back(action);
    return action;
}

void Actions::Serialize(Archive & arc)
{
    arc(_velocityActions, "platformVelocityActions");
    arc(_positionActions, "platformPositionActions");
    arc(_scaleActions, "platformScaleActions");
    arc.system(_positionSystem, "position");
    arc.system(_drawableSystem, "drawable");
}

static Point TweenPosition(
    ValueAction<sf::Vector2f> & action, 
    float beforeRatio,
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

void Actions::ApplyScaleActions(DrawableComponent & drawableComponent, float delta)
{
    for(auto& action : _scaleActions)
    {
        Drawable * drawable = nullptr;
        if (action->drawableKey() == "") 
        {
            drawable = drawableComponent.topDrawable();
        }
        else 
        {
            drawable = drawableComponent.GetDrawable(action->drawableKey());
        }

        float beforeRatio = action->tweenRatio();
        action->Update(delta);
        auto scale = TweenPosition(*action, beforeRatio, drawable->scale());
        drawable->scale(scale);
    }
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

void Actions::Apply(PositionComponent & position, DrawableComponent & drawable, float delta)
{

    RemoveDoneActions<VectorActionProxy>(_velocityActions);
    RemoveDoneActions<VectorActionProxy>(_positionActions);
    RemoveDoneActions<ScaleActionProxy>(_scaleActions);
    
    //Velocity actions apply additively
    Point velocity = ApplyVelocityActions(position, delta);

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

    ApplyScaleActions(drawable, delta);
}
