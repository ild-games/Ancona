#include <SFML/Window.hpp>

#include <Ancona/Game/Systems/KeyboardPlayerComponent.hpp>

using namespace ild;

KeyboardPlayerComponent::KeyboardPlayerComponent(PositionComponent & positionComponent)
    : _positionComponent(positionComponent)
{
}

void KeyboardPlayerComponent::Update()
{
    sf::Vector3f velocity;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        velocity.y -= SPEED;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        velocity.y += SPEED;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        velocity.x += SPEED;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        velocity.x -= SPEED;
    }

    _positionComponent.Velocity() = velocity;
}
