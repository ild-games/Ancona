#include "WindowImpl.hpp"

#include <SFML/System.hpp>


/* Pimpl Implementation */

WindowImpl::WindowImpl(
    const std::string& title,
    int width,
    int height,
    unsigned int style = WindowStyle::Default)
    : _sfmlWindow(sf::VideoMode(width, height), title, style) 
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

Window::sayHello()
{
    ILD_Log("hello from SFML")
}
