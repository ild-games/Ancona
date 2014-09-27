#include <Ancona/Engine/Screen/ScreenManager.hpp>

using namespace ild;

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

void ScreenManager::Render()
{
    _screens.top()->Render();
}
