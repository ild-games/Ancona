#include <Ancona/Platformer/Actions/JumpAction.hpp>

using namespace ild;

void JumpAction::AddEvent(JumpEvent event)
{
    _events.push_back(event);
}

void JumpAction::ApplyJumpEvents(sf::Vector2f totalGravity)
{
    sf::Vector2f jumpGravityDifference = JumpGravityDifference(totalGravity);
    for (auto & event : _events)
    {
        switch (event) {
            case JumpEvent::Stop:
                _velocityAction->value(jumpGravityDifference);
                break;
            case JumpEvent::HitCeiling:
                _velocityAction->value(_velocityAction->value() - jumpGravityDifference);
                break;
            case JumpEvent::LetGo:
                jumpGravityDifference.y *= _reducedByPercentage;
                _velocityAction->value(_velocityAction->value() - jumpGravityDifference);
                break;
        }
    }
    _events.clear();
}

sf::Vector2f JumpAction::JumpGravityDifference(sf::Vector2f totalGravity)
{
    return sf::Vector2f(0, fmin(_velocityAction->value().y + totalGravity.y, 0));
}

void JumpAction::Serialize(Archive & arc)
{
    arc(_jumpSpeed, "jumpSpeed");
    arc(_reducedByPercentage, "reducedByPercentage");
}

/* getters and setters */
JumpAction * JumpAction::jumpSpeed(float jumpSpeed)
{
    _jumpSpeed = jumpSpeed;
    _velocityAction->value(sf::Vector2f(0, -jumpSpeed));
    return this;
}
