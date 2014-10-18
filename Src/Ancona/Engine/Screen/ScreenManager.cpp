#include <Ancona/Engine/Screen/ScreenManager.hpp>
#include <Ancona/Engine/Screen/AbstractScreen.hpp>
#include <SFML/Graphics.hpp>

using namespace ild;

ScreenManager::ScreenManager(sf::RenderWindow & window)
    : Window(window) 
{
}

void ScreenManager::Push(AbstractScreen * screen)
{
    _screens.push(screen);
}

void ScreenManager::Pop()
{
    delete _screens.top();
    _screens.pop();
}

void ScreenManager::Update(float delta)
{
    auto screen = _screens.top();
    if(!screen->__Initialized)
    {
        screen->Init();
        screen->__Initialized = true;
    }
    screen->Update(delta);
}

void ScreenManager::Draw()
{
    _screens.top()->Draw();
}

