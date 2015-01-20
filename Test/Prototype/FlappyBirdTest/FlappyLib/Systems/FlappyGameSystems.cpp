#include "FlappyGameSystems.hpp"

using namespace ild;

FlappyGameSystems::FlappyGameSystems(sf::RenderWindow & window)
{
    _manager = new SystemManager();
    _position = new PositionSystem(*_manager);
    _input = new InputControlSystem(*_manager);
    _gravity = new SimpleGravitySystem(*_manager);
    _flappyRotate = new FlappyRotateSystem(*_manager);
    _pipeSpawner = new PipeSpawnerSystem(*_manager);
    _collision = new CollisionSystem(*_manager, *_position);
    _drawable = new DrawableSystem(
            window,
            *_manager,
            *_position);
}
