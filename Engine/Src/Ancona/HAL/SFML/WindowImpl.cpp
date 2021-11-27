#include <SFML/System.hpp>

#include <Ancona/HAL/Keyboard.hpp>
#include <Ancona/HAL/Mouse.hpp>
#include <Ancona/HAL/Sensor.hpp>
#include <Ancona/HAL/SFML/EventImpl.hpp>
#include <Ancona/HAL/SFML/WindowImpl.hpp>
#include <Ancona/System/Log.hpp>
#include <Ancona/Util/Vector2.hpp>

using namespace ildhal;

/* Pimpl Implementation */

priv::WindowImpl::WindowImpl(
    const std::string & title,
    int width,
    int height,
    unsigned int style) :
        RenderTargetImpl(std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), title, style))
{
}

/* HAL Interface Implementation */

Window::Window(
    const std::string& title,
    int width,
    int height,
    unsigned int style)
{
    _pimpl = std::make_unique<priv::RenderTargetImpl>(priv::WindowImpl(title, width, height, style));
}

Window::~Window() { }

void Window::SetFramerateLimit(unsigned int limit)
{
    getWindowImpl().getSfmlRenderWindow().setFramerateLimit(limit);
}

void Window::SetVerticalSyncEnabled(bool enabled)
{
    getWindowImpl().getSfmlRenderWindow().setVerticalSyncEnabled(enabled);
}

void Window::SetKeyRepeatEnabled(bool enabled)
{
    getWindowImpl().getSfmlRenderWindow().setKeyRepeatEnabled(enabled);
}

bool Window::IsOpen() const
{
    return getWindowImpl().getSfmlRenderWindow().isOpen();
}

bool Window::PollEvent(Event & event)
{
    sf::Event sfmlEvent;
    bool pollingSuccessful = getWindowImpl().getSfmlRenderWindow().pollEvent(sfmlEvent);
    priv::EventImpl::TranslateSFMLToAncona(sfmlEvent, event);
    return pollingSuccessful;
}

void Window::Display()
{
    getWindowImpl().getSfmlRenderWindow().display();
}

void Window::Close()
{
    getWindowImpl().getSfmlRenderWindow().close();
}

bool Window::SetActive(bool active) const
{
    return getWindowImpl().getSfmlRenderWindow().setActive(active);
}

void Window::SetTitle(const std::string & title)
{
    getWindowImpl().getSfmlRenderWindow().setTitle(title);
}

ild::Vector2u Window::GetSize() const
{
    auto size = getWindowImpl().getSfmlRenderWindow().getSize();
    return ild::Vector2u(size.x, size.y);
}

sf::RenderTarget & Window::GetRenderTarget()
{
    return getWindowImpl().getSfmlRenderWindow();
}

priv::WindowImpl & Window::getWindowImpl() const { return static_cast<priv::WindowImpl &>(getRenderTargetImpl()); }
