#include <SFML/System.hpp>

#include <Ancona/Core2D/Core/Game.hpp>
#include <Ancona/Core2D/InputDevices/Joystick.hpp>
#include <Ancona/Core2D/InputDevices/Keyboard.hpp>
#include <Ancona/Core2D/InputDevices/Mouse.hpp>
#include <Ancona/Core2D/InputDevices/Touch.hpp>
#include <Ancona/Framework/Audio/Jukebox.hpp>
#include <Ancona/Framework/Resource/ResourceLibrary.hpp>
#include <Ancona/Framework/Screens/ScreenManager.hpp>
#include <Ancona/System/EventHandling.hpp>
#include <Ancona/System/Log.hpp>
#include <Ancona/Util/Timer.hpp>
#include <Ancona/Framework/Resource/ResourceLoaderInit.hpp>

using namespace ild;

Game::Game(
    int windowWidth,
    int windowHeight,
    const std::string& title,
    const sf::Uint32& style)
    : _window(sf::VideoMode(windowWidth, windowHeight), title, style)
{
    _screenManager = std::unique_ptr<ScreenManager>(new ScreenManager(_window, windowWidth, windowHeight));
}

Game::~Game()
{
    ResourceLibrary::GarbageCollect();
    ResourceLoaderInit::Destroy();
}

void Game::Run()
{
    sf::Clock clock;
    sf::Music* music = new sf::Music();
    Jukebox::InitMusic(music);
    _window.setFramerateLimit(60);
    _window.setVerticalSyncEnabled(true);
    _window.setKeyRepeatEnabled(false);

    while (_window.isOpen() && !_screenManager->Empty()) {
        sf::Event event;
        if (!_windowIsActive) {
            sf::sleep(sf::seconds(0.5f));
            while (_window.pollEvent(event)) {
                ProcessWindowEvent(event);
            }
            continue;
        }

        Keyboard::_ClearKeys();
        Mouse::_ClearButtons();
        Touch::_ClearFingers();
        Joystick::_ClearButtons();
        Jukebox::Update();
        while (_window.pollEvent(event)) {
            ProcessWindowEvent(event);
        }

        sf::Time elapsed = clock.restart();
        float delta = std::min(elapsed.asSeconds(), 0.0235f);
        Timer::Update(delta);
        _screenManager->Update(delta);
        _window.clear(sf::Color::Black);
        _screenManager->Draw(delta);
        _window.display();
    }
    Jukebox::StopMusic();
    delete music;
}

void Game::ProcessWindowEvent(sf::Event event)
{
    EventHandling::HandleEvent(event);

    if (event.type == sf::Event::Closed) {
        while (!_screenManager->Empty()) {
            _screenManager->PopImmediate();
        }
        _window.close();
    }
    if (event.type == sf::Event::LostFocus) {
        _window.setActive(false);
        _windowIsActive = false;
    }
    if (event.type == sf::Event::GainedFocus) {
        _window.setActive(true);
        _windowIsActive = true;
    }

    if (_windowIsActive) {
        if (event.type == sf::Event::KeyPressed) {
            Keyboard::_AddKeyPress(event.key.code);
        }
        if (event.type == sf::Event::KeyReleased) {
            Keyboard::_AddKeyRelease(event.key.code);
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            Mouse::_AddButtonPress(event.mouseButton.button);
        }
        if (event.type == sf::Event::MouseButtonReleased) {
            Mouse::_AddButtonRelease(event.mouseButton.button);
        }
        if (event.type == sf::Event::TouchBegan) {
            Touch::_AddFingerPress(event.touch.finger);
        }
        if (event.type == sf::Event::TouchEnded) {
            Touch::_AddFingerRelease(event.touch.finger);
        }
        if (event.type == sf::Event::JoystickButtonPressed) {
            Joystick::_AddButtonPress(event.joystickButton.joystickId, event.joystickButton.button);
        }
        if (event.type == sf::Event::JoystickButtonReleased) {
            Joystick::_AddButtonRelease(event.joystickButton.joystickId, event.joystickButton.button);
        }
    }
}
