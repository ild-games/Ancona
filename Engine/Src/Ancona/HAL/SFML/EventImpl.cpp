#include <Ancona/HAL/SFML/EventImpl.hpp>
#include <Ancona/HAL/Joystick.hpp>
#include <Ancona/HAL/Keyboard.hpp>
#include <Ancona/HAL/Mouse.hpp>
#include <Ancona/HAL/Sensor.hpp>

namespace ildhal
{

void priv::EventImpl::TranslateSfmlToAncona(const sf::Event & sfmlEvent, Event & event)
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

}
