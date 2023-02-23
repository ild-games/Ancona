#include <Ancona/HAL/BackButton.hpp>
#include <Ancona/HAL/Keyboard.hpp>

namespace ildhal
{

bool BackButton::IsPressed()
{
    return ildhal::Keyboard::IsKeyReleased(ildhal::Keyboard::Escape);
}

} // namespace ildhal
