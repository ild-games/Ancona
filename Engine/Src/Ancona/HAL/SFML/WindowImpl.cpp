#include <SFML/Graphics.hpp>

#include <Ancona/HAL/Keyboard.hpp>
#include <Ancona/HAL/Mouse.hpp>
#include <Ancona/HAL/SFML/EventImpl.hpp>
#include <Ancona/HAL/SFML/WindowImpl.hpp>
#include <Ancona/HAL/Sensor.hpp>
#include <Ancona/System/Log.hpp>
#include <Ancona/Util/Vector2.hpp>

namespace ildhal
{

/* Pimpl Implementation */

priv::WindowImpl::WindowImpl(const std::string &title, int width, int height, unsigned int style)
{
    _sfmlRenderTarget = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), title, style);
}

sf::RenderWindow &priv::WindowImpl::sfmlRenderWindow() const
{
    return static_cast<sf::RenderWindow &>(*_sfmlRenderTarget);
}

/* HAL Interface Implementation */

Window::Window(const std::string &title, int width, int height, unsigned int style)
{
    _pimpl = std::make_unique<priv::WindowImpl>(title, width, height, style);
}

bool Window::PollEvent(Event &event)
{
    sf::Event sfmlEvent;
    bool pollingSuccessful = windowImpl().sfmlRenderWindow().pollEvent(sfmlEvent);
    priv::EventImpl::TranslateSfmlToAncona(sfmlEvent, event);
    return pollingSuccessful;
}

void Window::Display()
{
    windowImpl().sfmlRenderWindow().display();
}

void Window::Close()
{
    windowImpl().sfmlRenderWindow().close();
}

/* getters and setters */

ild::Vector2u Window::size() const
{
    auto size = windowImpl().sfmlRenderWindow().getSize();
    return ild::Vector2u(size.x, size.y);
}

void Window::title(const std::string &title)
{
    windowImpl().sfmlRenderWindow().setTitle(title);
}

bool Window::active(bool active) const
{
    return windowImpl().sfmlRenderWindow().setActive(active);
}

bool Window::open() const
{
    return windowImpl().sfmlRenderWindow().isOpen();
}

void Window::keyRepeatEnabled(bool enabled)
{
    windowImpl().sfmlRenderWindow().setKeyRepeatEnabled(enabled);
}

void Window::verticalSyncEnabled(bool enabled)
{
    windowImpl().sfmlRenderWindow().setVerticalSyncEnabled(enabled);
}

void Window::framerateLimit(unsigned int limit)
{
    windowImpl().sfmlRenderWindow().setFramerateLimit(limit);
}

priv::WindowImpl &Window::windowImpl() const
{
    return static_cast<priv::WindowImpl &>(*_pimpl);
}

} // namespace ildhal
