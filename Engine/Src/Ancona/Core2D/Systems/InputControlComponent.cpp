#include <Ancona/Core2D/Systems/InputControlComponent.hpp>

using namespace ild;

InputControlComponent::InputControlComponent(
        InputHandler & handler)
    : _handler(handler)
{
}

void InputControlComponent::Update(float delta)
{
    _handler.HandleInput(delta);    
}
