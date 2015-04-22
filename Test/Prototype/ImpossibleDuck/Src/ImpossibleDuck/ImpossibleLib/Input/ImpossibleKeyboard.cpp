#include <iostream>

#include <Ancona/Core2D/InputDevices/Keyboard.hpp>
#include "../Systems/ImpossibleGameSystems.hpp"
#include "ImpossibleKeyboard.hpp"

using namespace ild;

void ImpossibleKeyboard::HandleInput()
{

    if(Keyboard::IsKeyDown(sf::Keyboard::Space))
    {
        _playerComponent->Jump();
    }
    else
    {
        _playerComponent->GoDirection(NO_DIR);
    }

    if(Keyboard::IsKeyPressed(sf::Keyboard::F))
    {
        Entity player = _systems->systemManager().GetEntity("player");
        _systems->fadeDrawable().CreateComponent(
                player,
                *_systems->drawable()[player],
                false);
    }
}

