#include <Ancona/Platformer/Actions/Actions.hpp>
#include <Ancona/System/Log.hpp>
#include <Ancona/Util/Algorithm/ContainerWrappers.hpp>

using namespace ild;

Actions::Actions(PositionSystem *positionSystem, DrawableSystem *drawableSystem)
    : _positionSystem(positionSystem), _drawableSystem(drawableSystem)
{
}

VectorActionProxy Actions::CreatePositionAction()
{
    VectorActionProxy action(new ValueAction<Vector2f>());
    _positionActions.push_back(action);
    return action;
}

VectorActionProxy Actions::CreateVelocityAction()
{
    VectorActionProxy action(new ValueAction<Vector2f>());
    _velocityActions.push_back(action);
    return action;
}

ScaleActionProxy Actions::CreateScaleAction(std::string drawableKey)
{
    ScaleActionProxy action(new ScaleAction<Vector2f>(drawableKey));
    _scaleActions.push_back(action);
    return action;
}

void Actions::Serialize(Archive &arc)
{
    arc(_velocityActions, "platformVelocityActions");
    arc(_positionActions, "platformPositionActions");
    arc(_scaleActions, "platformScaleActions");
    arc.system(_positionSystem, "position");
    arc.system(_drawableSystem, "drawable");
}

static Vector2f TweenPosition(ValueAction<Vector2f> &action, float beforeRatio, const Vector2f &position)
{
    float afterRatio = action.tweenRatio();

    if (afterRatio == 1)
    {
        return action.value();
    }

    return position + (afterRatio - beforeRatio) / (1 - beforeRatio) * (action.value() - position);
}

void Actions::ApplyScaleActions(DrawableComponent &drawableComponent, float delta)
{
    for (auto &action : _scaleActions)
    {
        Drawable *drawable = nullptr;
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

Vector2f Actions::ApplyPositionActions(const PositionComponent &position, float delta)
{
    Vector2f location = position.position();
    for (auto &action : _positionActions)
    {
        float beforeRatio = action->tweenRatio();
        action->Update(delta);
        location = TweenPosition(*action, beforeRatio, position.position());
    }
    return location;
}

Vector2f Actions::ApplyVelocityActions(const PositionComponent &position, float delta)
{
    Vector2f velocity;
    for (auto &action : _velocityActions)
    {
        float overflow = action->Update(delta);
        auto value = action->value();

        if (overflow > 0)
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

void Actions::Apply(PositionComponent &position, DrawableComponent &drawable, float delta)
{

    RemoveDoneActions<VectorActionProxy>(_velocityActions);
    RemoveDoneActions<VectorActionProxy>(_positionActions);
    RemoveDoneActions<ScaleActionProxy>(_scaleActions);

    // Velocity actions apply additively
    Vector2f velocity = ApplyVelocityActions(position, delta);

    if (_positionActions.size())
    {
        // Only a single position action will effect the result
        position.position(ApplyPositionActions(position, delta));
        position.velocity(Vector2f());
    }
    else
    {
        auto diff = velocity - _actionVelocity;
        position.velocity(position.velocity() + diff);
        _actionVelocity = velocity;
    }

    ApplyScaleActions(drawable, delta);
}
