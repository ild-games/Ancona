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

unsigned long Game::FrameCount = 0;

Game::Game(const GameConfig &config)
    : _config(config),
      _window(std::make_unique<ildhal::Window>(config.title, config.windowWidth, config.windowHeight, config.style)),
      _music(std::make_shared<ildhal::Music>())
{
    _screenManager = std::make_unique<ScreenManager>(*_window, config.windowWidth, config.windowHeight);
    Jukebox::InitMusic(_music);
    if (config.isFpsLimited)
    {
        _window->framerateLimit(config.fpsLimit);
    }
    _window->verticalSyncEnabled(config.isVSyncEnabled);
    _window->keyRepeatEnabled(config.isKeyRepeatEnabled);
}

Game::~Game()
{
    Jukebox::StopMusic();
    ResourceLibrary::GarbageCollect();
    ResourceLoaderInit::Destroy();
}

void Game::InputUpdate(float deltaTime)
{
    _screenManager->InputUpdate(deltaTime);
}

void Game::FixedUpdate(float fixedDeltaTime)
{
    _screenManager->Update(fixedDeltaTime);
}

void Game::Render(float delta)
{
    _window->Clear(Color::Black);
    _screenManager->Draw(delta);
    _window->Display();
}

void Game::Run()
{
    unsigned int fpsFrames = 0;
    ildhal::Time fpsPreviousTime = ildhal::Time::Zero;
    ildhal::Time fpsCurrentTime = ildhal::Time::Zero;
    ildhal::Time fpsDisplayUpdateInterval = ildhal::seconds(1.0f);
    std::ostringstream fpsStream;

    ildhal::Clock clock;

    ildhal::Time minDeltaTime = ildhal::seconds(1.0f / _config.minFps);
    ildhal::Time totalTime = ildhal::Time::Zero;
    ildhal::Time fixedDeltaTime = ildhal::seconds(1.0f / _config.fixedUpdateFps);

    ildhal::Time currentTime = clock.ElapsedTime();
    ildhal::Time accumulator = ildhal::Time::Zero;

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
        Jukebox::Update();
        while (_window->PollEvent(event))
        {
            ProcessWindowEvent(event);
        }

        ildhal::Time newTime = clock.ElapsedTime();
        ildhal::Time deltaTime = ildhal::minTime(newTime - currentTime, minDeltaTime);
        currentTime = newTime;
        accumulator += deltaTime;

        // TODO get rid of this dumb thing and just use a HAL timer
        Timer::Update(deltaTime.AsSeconds());

        InputUpdate(deltaTime.AsSeconds());
        while (accumulator >= fixedDeltaTime)
        {
            FixedUpdate(fixedDeltaTime.AsSeconds());
            totalTime += fixedDeltaTime;
            accumulator -= fixedDeltaTime;

            // clear input after first FixedUpdate has had a chance to process input
            ildhal::Keyboard::_ClearKeys();
            ildhal::Mouse::_ClearButtons();
            ildhal::Touch::_ClearFingers();
            ildhal::Joystick::_ClearButtons();
        }
        ILD_Log(std::ostringstream() << "Accumulator: " << accumulator.AsSeconds());

        Render(deltaTime.AsSeconds());

        FrameCount++;

        fpsFrames++;
        fpsCurrentTime = clock.ElapsedTime();
        if (fpsCurrentTime - fpsPreviousTime >= fpsDisplayUpdateInterval)
        {
            fpsStream.str("");
            fpsStream.clear();
            fpsStream << "FPS: " << fpsFrames << std::endl;
            _window->title(fpsStream.str());
            fpsFrames = 0;
            fpsPreviousTime = fpsCurrentTime;
        }
    }
}

void Game::RunOld()
{
    unsigned int fpsFrames = 0;
    ildhal::Clock fpsClock;
    ildhal::Time fpsPreviousTime = fpsClock.ElapsedTime();
    ildhal::Time fpsCurrentTime;
    std::ostringstream fpsStream;

    ildhal::Clock clock;

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
        // float delta = elapsed.AsSeconds();
        float delta = std::min(elapsed.AsSeconds(), 0.0235f);
        Timer::Update(delta);
        _screenManager->Update(delta);
        _window->Clear(Color::Black);
        _screenManager->Draw(delta);
        _window->Display();
        FrameCount++;

        fpsFrames++;
        fpsCurrentTime = fpsClock.ElapsedTime();
        if (fpsCurrentTime.AsSeconds() - fpsPreviousTime.AsSeconds() >= 1.0f)
        {
            fpsStream.str("");
            fpsStream.clear();
            fpsStream << "FPS: " << fpsFrames << std::endl;
            _window->title(fpsStream.str());
            fpsFrames = 0;
            fpsPreviousTime = ildhal::seconds(fpsCurrentTime.AsSeconds());
        }
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
