#include <algorithm>
#include <Ancona/Engine/Core/Systems/Physics/VectorAction.hpp>

using namespace ild;

float VectorAction::GetTweenRatio()
{
    if(_tweenTime > 0)
    {
        return std::min(GetAge() / _tweenTime, 1.0f);
    }
    else
    {
        return 1;
    }
}

VectorAction * VectorAction::Tween(float time)
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
