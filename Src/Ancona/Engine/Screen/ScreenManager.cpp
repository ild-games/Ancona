#include <Ancona/Engine/Screen/ScreenManager.hpp>
#include <Ancona/Engine/Screen/AbstractScreen.hpp>
#include <SFML/Graphics.hpp>

using namespace ild;

ScreenManager::ScreenManager(sf::RenderWindow & window)
    : _window(window) 
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
    _screens.top()->Update(delta);
}

void ScreenManager::Draw()
{
    _screens.top()->Draw();
}

sf::RenderWindow & ScreenManager::GetWindow()
{
    return _window;
}
