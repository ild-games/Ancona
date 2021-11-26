#include <SDL2/SDL.h>
#include <SFML/System.hpp>

#include <Ancona/Core2D/Core/Game.hpp>
#include <Ancona/HAL/Joystick.hpp>
#include <Ancona/HAL/Keyboard.hpp>
#include <Ancona/HAL/Mouse.hpp>
#include <Ancona/HAL/Touch.hpp>
#include <Ancona/Framework/Audio/Jukebox.hpp>
#include <Ancona/Framework/Resource/ResourceLibrary.hpp>
#include <Ancona/Framework/Screens/ScreenManager.hpp>
#include <Ancona/System/EventHandling.hpp>
#include <Ancona/System/Log.hpp>
#include <Ancona/Util/Timer.hpp>
#include <Ancona/Framework/Resource/ResourceLoaderInit.hpp>

using namespace ild;

unsigned int Game::FrameCount = 0;

Game::Game(
    int windowWidth,
    int windowHeight,
    const std::string & title,
    const unsigned int & style) :
        _window(new ildhal::Window(title, windowWidth, windowHeight, style))
{
    _screenManager = std::unique_ptr<ScreenManager>(new ScreenManager(*_window, windowWidth, windowHeight));
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
    _window->setFramerateLimit(60);
    _window->setVerticalSyncEnabled(true);
    _window->setKeyRepeatEnabled(false);

    while (_window->isOpen() && !_screenManager->Empty()) {
        ildhal::Event event;
        if (!_windowIsActive) {
            sf::sleep(sf::seconds(0.5f));
            while (_window->pollEvent(event)) {
                ProcessWindowEvent(event);
            }
            continue;
        }

        ildhal::Keyboard::_ClearKeys();
        ildhal::Mouse::_ClearButtons();
        ildhal::Touch::_ClearFingers();
        ildhal::Joystick::_ClearButtons();
        Jukebox::Update();
        while (_window->pollEvent(event)) {
            ProcessWindowEvent(event);
        }

        sf::Time elapsed = clock.restart();
        float delta = std::min(elapsed.asSeconds(), 0.0235f);
        Timer::Update(delta);
        _screenManager->Update(delta);
        _window->clear(sf::Color::Black);
        _screenManager->Draw(delta);
        _window->display();
        FrameCount++;
    }
    Jukebox::StopMusic();
    delete music;
}

void Game::ProcessWindowEvent(ildhal::Event event)
{
    EventHandling::HandleEvent(event, _windowIsActive, *_window);

    if (event.type == ildhal::Event::Closed) {
        while (!_screenManager->Empty()) {
            _screenManager->PopImmediate();
        }
        _window->close();
    }
    if (event.type == ildhal::Event::LostFocus) {
        _windowIsActive = false;
        _window->setActive(false);
    }
    if (event.type == ildhal::Event::GainedFocus) {
        ildhal::Touch::_ClearAllFingersState();
        _windowIsActive = true;
        _window->resetGLStates();
        _window->setActive(true);
    }

    if (_windowIsActive) {
        if (event.type == ildhal::Event::KeyPressed) {
            ildhal::Keyboard::_AddKeyPress(event.key.code);
        }
        if (event.type == ildhal::Event::KeyReleased) {
            ildhal::Keyboard::_AddKeyRelease(event.key.code);
        }
        if (event.type == ildhal::Event::MouseButtonPressed) {
            ildhal::Mouse::_AddButtonPress(event.mouseButton.button);
        }
        if (event.type == ildhal::Event::MouseButtonReleased) {
            ildhal::Mouse::_AddButtonRelease(event.mouseButton.button);
        }
        if (event.type == ildhal::Event::TouchBegan) {
            ildhal::Touch::_AddFingerPress(event.touch.finger, event.touch.x, event.touch.y);
        }
        if (event.type == ildhal::Event::TouchEnded) {
            ildhal::Touch::_AddFingerRelease(event.touch.finger);
        }
        if (event.type == ildhal::Event::TouchMoved) {
            ildhal::Touch::_AddFingerMoved(event.touch.finger, event.touch.x, event.touch.y);
        }
        if (event.type == ildhal::Event::JoystickButtonPressed) {
            ildhal::Joystick::_AddButtonPress(event.joystickButton.joystickId, event.joystickButton.button);
        }
        if (event.type == ildhal::Event::JoystickButtonReleased) {
            ildhal::Joystick::_AddButtonRelease(event.joystickButton.joystickId, event.joystickButton.button);
        }
    }
}
