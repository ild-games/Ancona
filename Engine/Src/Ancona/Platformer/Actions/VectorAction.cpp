#include <algorithm>
#include <Ancona/Core2D/Systems/Position/PositionSystem.hpp>
#include <Ancona/Platformer/Actions/VectorAction.hpp>

using namespace ild;

float VectorAction::tweenRatio()
{
    if(_tweenTime > 0)
    {
        return std::min(age() / _tweenTime, 1.0f);
    }
    else
    {
        return 1;
    }
}

VectorAction * VectorAction::tween(float time)
{
    _tweenTime = time;
    return this;
}

void VectorAction::Serialize(Archive & arc)
{
    Action::Serialize(arc);
    arc(_tweenTime, "tween");
    arc(_value, "value");
}