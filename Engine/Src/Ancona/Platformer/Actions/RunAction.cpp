#include <Ancona/Platformer/Actions/RunAction.hpp>
#include <Ancona/Util/Algorithm/ContainerExtensions.hpp>

using namespace ild;

void RunAction::AddEvent(RunEvent event)
{
    if (event == RunEvent::MoveLeft || event == RunEvent::MoveRight)
    {
        _events.push_back(event);
    }
    else if (event == RunEvent::StopMoveLeft)
    {
        auto leftEvent = RunEvent::MoveLeft;
        alg::erase(_events, leftEvent);
    }
    else if (event == RunEvent::StopMoveRight)
    {
        auto rightEvent = RunEvent::MoveRight;
        alg::erase(_events, rightEvent);
    }
}

void RunAction::ApplyRunEvents()
{
    if (_events.size() == 0)
    {
        GravitateTowards(0);
    }
    else
    {
        auto event = _events.back();
        switch (event)
        {
            case MoveLeft:
                GravitateTowards(-_maxSpeed);
                break;
            case MoveRight:
                GravitateTowards(_maxSpeed);
                break;
        }
    }

    _velocityAction->value(sf::Vector2f(_currentSpeed, 0));
}

void RunAction::Cancel()
{
    Action::Cancel();
    _velocityAction->Cancel();
}

void RunAction::Serialize(Archive & arc)
{
    arc(_maxSpeed, "maxSpeed");
    arc(_currentSpeed, "currentSpeed");
    arc(_acceleration, "acceleration");
}

void RunAction::GravitateTowards(float destination)
{
    if (_currentSpeed < destination)
    {
        _currentSpeed = std::min(_currentSpeed + _acceleration, destination);
    }
    else
    {
        _currentSpeed = std::max(_currentSpeed - _acceleration, destination);
    }
}
