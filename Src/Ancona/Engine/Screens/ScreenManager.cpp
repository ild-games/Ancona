#include <Ancona/Engine/Screens/ScreenManager.hpp>
#include <Ancona/Engine/Screens/LoadingScreen.hpp>
#include <Ancona/Engine/Screens/AbstractScreen.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

using namespace ild;

ScreenManager::ScreenManager(sf::RenderWindow & window)
    : Window(window) 
{
}

void ScreenManager::Push(AbstractScreen * screen, bool load)
{
    _screens.push(screen);
    screen->__Entering = true;
    if(load) 
    {
        Push(new LoadingScreen(screen, *this), false);
    }
}

void ScreenManager::Pop()
{
    _screens.top()->__Exiting = true;
}

void ScreenManager::Replace(AbstractScreen * screen)
{
    Pop();
    _replacementScreen = screen;
}

void ScreenManager::Update(float delta)
{
    if(!Empty())
    {
        auto screen = _screens.top();
        if(!screen->__Initialized)
        {
            screen->Init();
            screen->__Initialized = true;
        }
        screen->Update(delta);
    }
}

void ScreenManager::Draw(float delta)
{
    if(!Empty())
    {
        _screens.top()->Draw(delta);

        // Entering and exiting code is run after the screen is draw,
        // this is so drawing done at these steps (such as transitions)
        // can be drawn over all other elements.
        if(_screens.top()->__Entering)
        {
            _screens.top()->Entering(delta);
        }
        else if(_screens.top()->__Exiting)
        {
            _screens.top()->Exiting(delta);
            // if done exiting, remove the screen
            if(!_screens.top()->__Exiting)
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
    delete _screens.top();
    _screens.pop();
    if(_replacementScreen != nullptr)
    {
        Push(_replacementScreen);
        _replacementScreen = nullptr;
    }
}
