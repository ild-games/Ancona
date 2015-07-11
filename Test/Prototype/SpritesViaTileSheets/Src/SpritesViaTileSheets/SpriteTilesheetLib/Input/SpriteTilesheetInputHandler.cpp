#include <Ancona/Core2D/InputDevices/InputHandler.hpp>

#include "../Systems/SpriteTilesheetGameSystems.hpp"
#include "SpriteTilesheetInputHandler.hpp"

using namespace ild;

///////////////////////////////
// SpriteTilesheetInputHandler
void SpriteTilesheetInputHandler::RegisterInputComponent(SpriteTilesheetInputComponent * component)
{
    _playerComponent = component;
}

///////////////////////////////
// SpriteTilesheetInputComponent
SpriteTilesheetInputComponent::SpriteTilesheetInputComponent(
        const Entity & player,
        SpriteTilesheetGameSystems & systems,
        SpriteTilesheetInputHandler & inputHandler) :
    InputControlComponent(inputHandler)
{
    inputHandler.RegisterInputComponent(this);
}
