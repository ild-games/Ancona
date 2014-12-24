#include "FlappyTouch.hpp"
#include "../Systems/FlappyInputComponent.hpp"

#include <SFML/Window.hpp>

using namespace ild;

void FlappyTouch::HandleInput()
{
    if(sf::Touch::isDown(0))
    {
        _component->Jump();
    }
}

void FlappyTouch::RegisterInputComponent(FlappyInputComponent * component)
{
    _component = component;
}
