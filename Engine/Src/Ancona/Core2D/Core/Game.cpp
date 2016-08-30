#include <Ancona/Core2D/Core/Game.hpp>
#include <Ancona/Framework/Screens/ScreenManager.hpp>
#include <Ancona/Core2D/InputDevices/Keyboard.hpp>
#include <Ancona/Core2D/InputDevices/Mouse.hpp>
#include <Ancona/Core2D/InputDevices/Touch.hpp>

using namespace ild;

Game::Game(int windowWidth, int windowHeight, const std::string & title)
    : _window(sf::VideoMode(windowWidth, windowHeight), title)
{
    _screenManager = new ScreenManager(_window);
}

void Game::Run()
{
    sf::Clock clock;
    _window.setFramerateLimit(60);
    _window.setKeyRepeatEnabled(false);
    while (_window.isOpen() && !_screenManager->Empty())
    {
        sf::Event event;
        Keyboard::_ClearKeys();
        Mouse::_ClearButtons();
        Touch::_ClearFingers();
        while (_window.pollEvent(event))
        {
            ProcessWindowEvent(event);
        }

        sf::Time elapsed = clock.restart();
        float delta = elapsed.asSeconds();
        _screenManager->Update(delta);

        _window.clear(sf::Color::Black);
        _screenManager->Draw(delta);
        _window.display();
    }
}

void Game::ProcessWindowEvent(sf::Event event)
{
    if (event.type == sf::Event::Closed)
    {
        _window.close();
    }
    if (event.type == sf::Event::KeyPressed)
    {
        Keyboard::_AddKeyPress(event.key.code);
    }
    if (event.type == sf::Event::KeyReleased)
    {
        Keyboard::_AddKeyRelease(event.key.code);
    }
    if (event.type == sf::Event::MouseButtonPressed)
    {
        Mouse::_AddButtonPress(event.mouseButton.button);
    }
    if (event.type == sf::Event::MouseButtonReleased)
    {
        Mouse::_AddButtonRelease(event.mouseButton.button);
    }
    if (event.type == sf::Event::TouchBegan)
    {
        Touch::_AddFingerPress(event.touch.finger);
    }
    if (event.type == sf::Event::TouchEnded)
    {
        Touch::_AddFingerRelease(event.touch.finger);
    }
}
