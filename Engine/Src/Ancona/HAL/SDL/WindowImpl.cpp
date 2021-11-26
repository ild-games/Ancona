#include <Ancona/HAL/SFML/WindowImpl.hpp>
#include <Ancona/System/Log.hpp>

using namespace ildhal;

/* Pimpl Implementation */

Window::Impl::Impl(
    const std::string& title,
    int width,
    int height,
    unsigned int style)
{
}

/* Pimpl Interface */

Window::Window(
    const std::string& title,
    int width,
    int height,
    unsigned int style)
    : _pimpl(new Window::Impl(title, width, height, style))
{
}

Window::~Window() { }
