#include "WindowImpl.hpp"


/* Pimpl Implementation */

WindowImpl::WindowImpl(
    const std::string& title,
    int width,
    int height,
    unsigned int style = WindowStyle::Default)
{
}


/* Pimpl Interface */

Window::Window(
    const std::string& title,
    int width,
    int height,
    unsigned int style = WindowStyle::Default)
    : _pimpl(new WindowImpl(title, width, height, style))
{
}


Window::~Window() { }

Window::sayHello()
{
    ILD_Log("hello from SDL")
}
