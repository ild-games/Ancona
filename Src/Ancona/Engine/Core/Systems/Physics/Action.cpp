#include <Ancona/Engine/Core/Systems/Physics/Action.hpp>

using namespace ild;

Action::Action()
{
    _priority = 0;
    _duration = 0;
}

void Action::Cancel()
{
    _duration = -1;
}

void Action::Update(float delta)
{
    if(!Done())
    {
        _duration -= delta;
    }
}
