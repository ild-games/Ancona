#include <SFML/System.hpp>

#include <Ancona/HAL/Keyboard.hpp>
#include <Ancona/HAL/Mouse.hpp>
#include <Ancona/HAL/Sensor.hpp>
#include <Ancona/HAL/SFML/WindowImpl.hpp>
#include <Ancona/System/Log.hpp>

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

void priv::WindowImpl::TranslateEventFromSFML(Event & event, sf::Event & sfmlEvent)
{
    event.type = (Event::EventType) sfmlEvent.type;
    if (sfmlEvent.type == sf::Event::Resized)
    {
        event.size.width = sfmlEvent.size.width;
        event.size.height = sfmlEvent.size.height;
    }
    else if (sfmlEvent.type == sf::Event::KeyPressed || sfmlEvent.type == sf::Event::KeyReleased)
    {
        event.key.code = (Keyboard::Key) sfmlEvent.key.code;
        event.key.alt = sfmlEvent.key.alt;
        event.key.control = sfmlEvent.key.control;
        event.key.shift = sfmlEvent.key.shift;
        event.key.system = sfmlEvent.key.system;
    }
    else if (sfmlEvent.type == sf::Event::TextEntered)
    {
        event.text.unicode = sfmlEvent.text.unicode;
    }
    else if (sfmlEvent.type == sf::Event::MouseMoved)
    {
        event.mouseMove.x = sfmlEvent.mouseMove.x;
        event.mouseMove.y = sfmlEvent.mouseMove.y;
    }
    else if (sfmlEvent.type == sf::Event::MouseButtonPressed || sfmlEvent.type == sf::Event::MouseButtonReleased)
    {
        event.mouseButton.button = (Mouse::Button) sfmlEvent.mouseButton.button;
        event.mouseButton.x = sfmlEvent.mouseButton.x;
        event.mouseButton.y = sfmlEvent.mouseButton.y;
    }
    else if (sfmlEvent.type == sf::Event::MouseWheelMoved)
    {
        event.mouseWheel.delta = sfmlEvent.mouseWheel.delta;
        event.mouseWheel.x = sfmlEvent.mouseWheel.x;
        event.mouseWheel.y = sfmlEvent.mouseWheel.y;
    }
    else if (sfmlEvent.type == sf::Event::MouseWheelScrolled)
    {
        event.mouseWheelScroll.wheel = (Mouse::Wheel) sfmlEvent.mouseWheelScroll.wheel;
        event.mouseWheelScroll.delta = sfmlEvent.mouseWheelScroll.delta;
        event.mouseWheelScroll.x = sfmlEvent.mouseWheelScroll.x;
        event.mouseWheelScroll.y = sfmlEvent.mouseWheelScroll.y;
    }
    else if (sfmlEvent.type == sf::Event::JoystickMoved)
    {
        event.joystickMove.joystickId = sfmlEvent.joystickMove.joystickId;
        event.joystickMove.axis = (Joystick::Axis) sfmlEvent.joystickMove.axis;
        event.joystickMove.position = sfmlEvent.joystickMove.position;
    }
    else if (sfmlEvent.type == sf::Event::JoystickButtonPressed || sfmlEvent.type == sf::Event::JoystickButtonReleased)
    {
        event.joystickButton.joystickId = sfmlEvent.joystickButton.joystickId;
        event.joystickButton.button = sfmlEvent.joystickButton.button;
    }
    else if (sfmlEvent.type == sf::Event::JoystickConnected || sfmlEvent.type == sf::Event::JoystickDisconnected)
    {
        event.joystickConnect.joystickId = sfmlEvent.joystickConnect.joystickId;
    }
    else if (sfmlEvent.type == sf::Event::TouchBegan || sfmlEvent.type == sf::Event::TouchMoved || sfmlEvent.type == sf::Event::TouchEnded)
    {
        event.touch.finger = sfmlEvent.touch.finger;
        event.touch.x = sfmlEvent.touch.x;
        event.touch.y = sfmlEvent.touch.y;
    }
    else if (sfmlEvent.type == sf::Event::SensorChanged)
    {
        event.sensor.type = (Sensor::Type) sfmlEvent.sensor.type;
        event.sensor.x = sfmlEvent.sensor.x;
        event.sensor.y = sfmlEvent.sensor.y;
        event.sensor.z = sfmlEvent.sensor.z;
    }
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
    getWindowImpl().TranslateEventFromSFML(event, sfmlEvent);
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

sf::Vector2u Window::GetSize() const
{
    return getWindowImpl().getSfmlRenderWindow().getSize();
}

sf::RenderTarget & Window::GetRenderTarget()
{
    return getWindowImpl().getSfmlRenderWindow();
}

priv::WindowImpl & Window::getWindowImpl() const { return static_cast<priv::WindowImpl &>(getRenderTargetImpl()); }
