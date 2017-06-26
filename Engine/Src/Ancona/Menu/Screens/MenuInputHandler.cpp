#include <algorithm>

#include <Ancona/Core2D/InputDevices/InputHandler.hpp>
#include <Ancona/Util/Math.hpp>

#include "MenuGameSystems.hpp"
#include "MenuInputHandler.hpp"


using namespace ildmenu;

///////////////////////////////
// MenuInputHandler
void MenuInputHandler::RegisterInputComponent(MenuInputComponent * component)
{
    _playerComponent = component;
}

///////////////////////////////
// MenuInputComponent
MenuInputComponent::MenuInputComponent(
        MenuGameSystems & systems,
        std::shared_ptr<MenuInputHandler> inputHandler) :
    InputControlComponent(inputHandler),
    _systems(systems)
{

}

void MenuInputComponent::UpdatePointer(ild::Point location, bool isDown)
{
    _systems.button().Pointer(location, isDown);
}
