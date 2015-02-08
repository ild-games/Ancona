#include <algorithm>
#include <Ancona/Engine/Core/Systems/Physics/VectorAction.hpp>

using namespace ild;

float VectorAction::GetTweenRatio()
{
    return std::min(GetAge() / _tweenTime, 1.0f);
}
