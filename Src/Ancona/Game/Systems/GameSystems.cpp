#include <Ancona/Game/Systems/GameSystems.hpp>

using namespace ild;

GameSystems::GameSystems(sf::RenderWindow & window)
{
    _manager = new SystemManager();
    _position = new PositionSystem(*_manager);
    _drawable = new DrawableSystem(window, *_manager, *_position);
    _input = new InputControlSystem(*_manager);
    _gravity = new SimpleGravitySystem(*_manager);
    _collision = new CollisionSystem(*_manager, *_position);
}
