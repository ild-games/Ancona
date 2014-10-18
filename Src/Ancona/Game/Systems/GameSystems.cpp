#include <Ancona/Game/Systems/GameSystems.hpp>

using namespace ild;

GameSystems::GameSystems(sf::RenderWindow & window)
{
    Manager = new SystemManager();
    Position = new PositionSystem(*Manager);
    Sprite = new SpriteSystem(window, *Manager,*Position);
    Input = new InputControlSystem(*Manager);
}
