#include <cmath>
#include <sstream>

#include <Ancona/Core2D/Core/Game.hpp>
#include <Ancona/Framework/Audio/Jukebox.hpp>
#include <Ancona/Framework/Resource/ResourceLibrary.hpp>
#include <Ancona/Framework/Resource/ResourceLoaderInit.hpp>
#include <Ancona/Framework/Screens/ScreenManager.hpp>
#include <Ancona/Graphics/Color.hpp>
#include <Ancona/HAL.hpp>
#include <Ancona/System/EventHandling.hpp>
#include <Ancona/System/Log.hpp>
#include <Ancona/Util/Timer.hpp>

using namespace ild;

unsigned int Game::FrameCount = 0;

Game::Game(int windowWidth, int windowHeight, const std::string &title, const unsigned int &style)
    : _window(std::make_unique<ildhal::Window>(title, windowWidth, windowHeight, style))
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
    ildhal::Clock fpsClock;
    ildhal::Time fpsPreviousTime = fpsClock.ElapsedTime();
    ildhal::Time fpsCurrentTime;
    std::ostringstream fpsStream;

    ildhal::Clock clock;
    std::shared_ptr<ildhal::Music> music = std::make_shared<ildhal::Music>();
    Jukebox::InitMusic(music);
    _window->framerateLimit(60);
    _window->verticalSyncEnabled(true);
    _window->keyRepeatEnabled(false);

    while (_window->open() && !_screenManager->Empty())
    {
        ildhal::Event event;
        if (!_windowIsActive)
        {
            ildhal::sleep(ildhal::seconds(0.5f));
            while (_window->PollEvent(event))
            {
                ProcessWindowEvent(event);
            }
            continue;
        }

        ildhal::Keyboard::_ClearKeys();
        ildhal::Mouse::_ClearButtons();
        ildhal::Touch::_ClearFingers();
        ildhal::Joystick::_ClearButtons();
        Jukebox::Update();
        while (_window->PollEvent(event))
        {
            ProcessWindowEvent(event);
        }

        ildhal::Time elapsed = clock.Restart();
        float delta = std::min(elapsed.AsSeconds(), 0.0235f);
        Timer::Update(delta);
        _screenManager->Update(delta);
        _window->Clear(Color::Black);
        _screenManager->Draw(delta);
        _window->Display();
        FrameCount++;

        fpsCurrentTime = fpsClock.ElapsedTime();
        fps = 1.0f / (fpsCurrentTime.AsSeconds() - fpsPreviousTime.AsSeconds());
        fpsPreviousTime = ildhal::seconds(fpsCurrentTime.AsSeconds());
        fpsStream.str("");
        fpsStream.clear();
        fpsStream << "FPS: " << (int)std::round(fps) << std::endl;
        _window->title(fpsStream.str());
    }
    Jukebox::StopMusic();
}

void Game::ProcessWindowEvent(ildhal::Event event)
{
    EventHandling::HandleEvent(event, _windowIsActive, *_window);

    if (event.type == ildhal::Event::Closed)
    {
        while (!_screenManager->Empty())
        {
            _screenManager->PopImmediate();
        }
        _window->Close();
    }
    if (event.type == ildhal::Event::LostFocus)
    {
        _windowIsActive = false;
        _window->active(false);
    }
    if (event.type == ildhal::Event::GainedFocus)
    {
        ildhal::Touch::_ClearAllFingersState();
        _windowIsActive = true;
        _window->ResetGLStates();
        _window->active(true);
    }

    if (_windowIsActive)
    {
        if (event.type == ildhal::Event::KeyPressed)
        {
            ildhal::Keyboard::_AddKeyPress(event.key.code);
        }
        if (event.type == ildhal::Event::KeyReleased)
        {
            ildhal::Keyboard::_AddKeyRelease(event.key.code);
        }
        if (event.type == ildhal::Event::MouseButtonPressed)
        {
            ildhal::Mouse::_AddButtonPress(event.mouseButton.button);
        }
        if (event.type == ildhal::Event::MouseButtonReleased)
        {
            ildhal::Mouse::_AddButtonRelease(event.mouseButton.button);
        }
        if (event.type == ildhal::Event::TouchBegan)
        {
            ildhal::Touch::_AddFingerPress(event.touch.finger, event.touch.x, event.touch.y);
        }
        if (event.type == ildhal::Event::TouchEnded)
        {
            ildhal::Touch::_AddFingerRelease(event.touch.finger);
        }
        if (event.type == ildhal::Event::TouchMoved)
        {
            ildhal::Touch::_AddFingerMoved(event.touch.finger, event.touch.x, event.touch.y);
        }
        if (event.type == ildhal::Event::JoystickButtonPressed)
        {
            ildhal::Joystick::_AddButtonPress(event.joystickButton.joystickId, event.joystickButton.button);
        }
        if (event.type == ildhal::Event::JoystickButtonReleased)
        {
            ildhal::Joystick::_AddButtonRelease(event.joystickButton.joystickId, event.joystickButton.button);
        }
    }
}
