#include <Ancona/Core2D/InputDevices/InputHandler.hpp>

#include "../Systems/RotationGameSystems.hpp"
#include "RotationInputHandler.hpp"

using namespace ild;

///////////////////////////////
// RotationInputHandler
void RotationInputHandler::RegisterInputComponent(RotationInputComponent * component)
{
    _playerComponent = component;
}

///////////////////////////////
// RotationInputComponent
RotationInputComponent::RotationInputComponent(
        const Entity & player,
        RotationGameSystems & systems,
        RotationInputHandler & inputHandler) :
    InputControlComponent(inputHandler),
    _playerEntity(player),
    _systems(systems)
{
    inputHandler.RegisterInputComponent(this);
}
