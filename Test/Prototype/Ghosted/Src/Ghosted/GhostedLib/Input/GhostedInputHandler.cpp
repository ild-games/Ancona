#include <Ancona/Core2D/InputDevices/InputHandler.hpp>

#include "../Systems/GhostedGameSystems.hpp"
#include "GhostedInputHandler.hpp"

using namespace ild;

///////////////////////////////
// GhostedInputHandler
void GhostedInputHandler::RegisterInputComponent(GhostedInputComponent * component)
{
    _playerComponent = component;
}

///////////////////////////////
// GhostedInputComponent
GhostedInputComponent::GhostedInputComponent(
        const Entity & player,
        GhostedGameSystems & systems,
        GhostedInputHandler & inputHandler) :
    InputControlComponent(inputHandler),
    _playerEntity(player),
    _systems(systems)
{
    inputHandler.RegisterInputComponent(this);
}
