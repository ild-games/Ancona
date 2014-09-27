#include <SFML/Window.hpp>

#include <Ancona/Game/Screen/TestScreen.hpp>

using namespace ild;

TestScreen::TestScreen(ScreenManager & manager)
    : AbstractScreen(manager)
{
}

void TestScreen::Update(float delta)
{
}

void TestScreen::Draw()
{
    _manager.Window().clear(sf::Color::Green);
}
