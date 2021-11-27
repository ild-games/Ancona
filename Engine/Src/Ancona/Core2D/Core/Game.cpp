#include <cmath>
#include <sstream>

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
        _window(std::make_unique<ildhal::Window>(title, windowWidth, windowHeight, style))
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
    float fps;
    sf::Clock fpsClock;
    sf::Time fpsPreviousTime = fpsClock.getElapsedTime();
    sf::Time fpsCurrentTime;
    std::ostringstream fpsStream;

    sf::Clock clock;
    std::shared_ptr<sf::Music> music = std::make_shared<sf::Music>();
    Jukebox::InitMusic(music);
    // _window->SetFramerateLimit(60);
    // _window->SetVerticalSyncEnabled(true);
    _window->SetKeyRepeatEnabled(false);

    while (_window->IsOpen() && !_screenManager->Empty()) {
        ildhal::Event event;
        if (!_windowIsActive) {
            sf::sleep(sf::seconds(0.5f));
            while (_window->PollEvent(event)) {
                ProcessWindowEvent(event);
            }
            continue;
        }

        ildhal::Keyboard::_ClearKeys();
        ildhal::Mouse::_ClearButtons();
        ildhal::Touch::_ClearFingers();
        ildhal::Joystick::_ClearButtons();
        Jukebox::Update();
        while (_window->PollEvent(event)) {
            ProcessWindowEvent(event);
        }

        sf::Time elapsed = clock.restart();
        // float delta = std::min(elapsed.asSeconds(), 0.0235f);
        float delta = elapsed.asSeconds();
        Timer::Update(delta);
        _screenManager->Update(delta);
        _window->Clear(sf::Color::Black);
        _screenManager->Draw(delta);
        _window->Display();
        FrameCount++;

        fpsCurrentTime = fpsClock.getElapsedTime();
        fps = 1.0f / (fpsCurrentTime.asSeconds() - fpsPreviousTime.asSeconds());
        fpsPreviousTime = fpsCurrentTime;
        fpsStream.str("");
        fpsStream.clear();
        fpsStream << "FPS: " << (int) std::round(fps) << std::endl;
        _window->SetTitle(fpsStream.str());
    }
    Jukebox::StopMusic();
}

void Game::ProcessWindowEvent(ildhal::Event event)
{
    EventHandling::HandleEvent(event, _windowIsActive, *_window);

    if (event.type == ildhal::Event::Closed) {
        while (!_screenManager->Empty()) {
            _screenManager->PopImmediate();
        }
        _window->Close();
    }
    if (event.type == ildhal::Event::LostFocus) {
        _windowIsActive = false;
        _window->SetActive(false);
    }
    if (event.type == ildhal::Event::GainedFocus) {
        ildhal::Touch::_ClearAllFingersState();
        _windowIsActive = true;
        _window->ResetGLStates();
        _window->SetActive(true);
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
