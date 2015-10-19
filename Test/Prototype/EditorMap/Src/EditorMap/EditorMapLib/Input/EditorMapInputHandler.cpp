#include <Ancona/Core2D/InputDevices/InputHandler.hpp>

#include "../Systems/EditorMapGameSystems.hpp"
#include "EditorMapInputHandler.hpp"

using namespace ild;

///////////////////////////////
// EditorMapInputHandler
void EditorMapInputHandler::RegisterInputComponent(EditorMapInputComponent * component)
{
    _playerComponent = component;
}

///////////////////////////////
// EditorMapInputComponent
EditorMapInputComponent::EditorMapInputComponent(
        const Entity & player,
        EditorMapGameSystems & systems,
        EditorMapInputHandler & inputHandler) :
    InputControlComponent(inputHandler),
    _playerEntity(player),
    _systems(systems)
{
    inputHandler.RegisterInputComponent(this);
}
