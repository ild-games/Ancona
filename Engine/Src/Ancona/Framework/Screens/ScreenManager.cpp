#include <Ancona/Framework/Screens/ScreenManager.hpp>
#include <Ancona/Framework/Screens/LoadingScreen.hpp>
#include <Ancona/Framework/Screens/AbstractScreen.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

using namespace ild;

ScreenManager::ScreenManager(
        ildhal::Window & window,
        int windowWidth,
        int windowHeight) :
    Window(window),
    _windowWidth(windowWidth),
    _windowHeight(windowHeight)
{
}

ScreenManager::~ScreenManager()
{
    if (_replacementScreen != nullptr) {
        delete _replacementScreen;
    }
}

void ScreenManager::Push(AbstractScreen * screen, bool load)
{
    _screens.push(screen);
    screen->__Entering = true;
    if (load)
    {
        Push(new LoadingScreen(screen, *this), false);
    }
}

void ScreenManager::Pop()
{
    _screens.top()->__Exiting = true;
}

void ScreenManager::PopImmediate()
{
    RemoveScreen();
}

AbstractScreen * ScreenManager::Peek()
{
    return _screens.top();
}

void ScreenManager::Replace(AbstractScreen * screen)
{
    Pop();
    _replacementScreen = screen;
}

void ScreenManager::Update(float delta)
{
    if (!Empty())
    {
        auto screen = _screens.top();
        if(!screen->__Initialized)
        {
            screen->Init();
            screen->__Initialized = true;
        }
        screen->Update(delta);
        screen->systemsContainer()->systemManager().PostUpdate();
    }
}

void ScreenManager::Draw(float delta)
{
    if (!Empty())
    {
        _screens.top()->Draw(delta);

        // Entering and exiting code is run after the screen is drawn,
        // this is so drawing done at these steps (such as transitions)
        // can be drawn over all other elements.
        if (_screens.top()->__Entering)
        {
            _screens.top()->Entering(delta);
        }
        else if (_screens.top()->__Exiting)
        {
            _screens.top()->Exiting(delta);
            // if done exiting, remove the screen
            if (!_screens.top()->__Exiting)
            {
                RemoveScreen();
            }
        }
    }
}

bool ScreenManager::Empty()
{
    return _screens.empty();
}

void ScreenManager::RemoveScreen()
{
    _screens.top()->Unload();
    if (_screens.top()->systemsContainer()->profile() >= 0) {
        SaveScreen();
    }
    delete _screens.top();
    _screens.pop();

    if (_replacementScreen != nullptr) {
        Push(_replacementScreen);
        _replacementScreen = nullptr;
    } else if (!_screens.empty()) {
        _screens.top()->Resume();
    }
}

void ScreenManager::SaveScreen()
{
    // todo implement
}
