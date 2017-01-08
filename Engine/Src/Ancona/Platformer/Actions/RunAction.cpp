#include <Ancona/Platformer/Actions/RunAction.hpp>
#include <Ancona/Util/Algorithm/ContainerExtensions.hpp>

#include <iostream>

using namespace ild;

RunAction::RunAction(PositionComponent * positionComponent) :
    _positionComponent(std::unique_ptr<PositionComponent>(positionComponent))
{
}

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
    if (_lastPosition.x == _positionComponent->position().x)
    {
        _currentSpeed = 0;
    }
    _lastPosition = sf::Vector2f(_positionComponent->position());

    if (_events.size() == 0)
    {
        GravitateTowards(0, _deceleration);
    }
    else
    {
        auto event = _events.back();
        auto gravitateAmount = 0;
        switch (event)
        {
            case MoveLeft:
                gravitateAmount = _acceleration + (_currentSpeed > 0 ? _deceleration : 0);
                GravitateTowards(-_maxSpeed, gravitateAmount);
                break;
            case MoveRight:
                gravitateAmount = _acceleration + (_currentSpeed < 0 ? _deceleration : 0);
                GravitateTowards(_maxSpeed, gravitateAmount);
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
    arc(_deceleration, "deceleration");
}

void RunAction::GravitateTowards(float destination, float accelerationSpeed)
{
    if (_currentSpeed < destination)
    {
        _currentSpeed = std::min(_currentSpeed + accelerationSpeed, destination);
    }
    else
    {
        _currentSpeed = std::max(_currentSpeed - accelerationSpeed, destination);
    }
}
