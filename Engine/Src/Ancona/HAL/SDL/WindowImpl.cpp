#include <Ancona/HAL/SFML/WindowImpl.hpp>

using namespace ildhal;

/* Pimpl Implementation */

WindowImpl::WindowImpl(
    const std::string& title,
    int width,
    int height,
    unsigned int style)
{
}

/* HAL Interface Implementation */

Window::Window(
    const std::string& title,
    int width,
    int height,
    unsigned int style)
    : _pimpl(new priv::WindowImpl(title, width, height, style))
{
}

Window::~Window() { }
