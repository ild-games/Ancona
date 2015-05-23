#include <iostream>

#include "../Systems/ImpossibleGameSystems.hpp"
#include "ImpossibleTouch.hpp"

using namespace ild;

void ImpossibleTouch::HandleInput()
{

    if(sf::Touch::isDown(0))
    {
        _playerComponent->Jump();
    }
    else
    {
        _playerComponent->GoDirection(NO_DIR);
    }
}

