#include <Ancona/HAL/BackButton.hpp>
#include <Ancona/HAL/Keyboard.hpp>

namespace ildhal
{

bool BackButton::IsPressed()
{
    return ildhal::Keyboard::IsKeyPressed(ildhal::Keyboard::BackButton);
}

} // namespace ildhal
