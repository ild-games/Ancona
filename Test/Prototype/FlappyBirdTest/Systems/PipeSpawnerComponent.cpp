#include "PipeSpawnerComponent.hpp"

using namespace ild;

PipeSpawnerComponent::PipeSpawnerComponent(
        SpriteSystem & spriteSystem,
        PositionSystem & positionSystem,
        SystemManager & systemManager)
    : _spriteSystem(spriteSystem), 
      _positionSystem(positionSystem),
      _systemManager(systemManager)
{
    _clock = new sf::Clock();
}

void PipeSpawnerComponent::Update()
{    
    if(_clock->getElapsedTime().asSeconds() > 1.5f)
    {
        SpawnPipePair();
        _clock->restart();
    }
}

void PipeSpawnerComponent::SpawnPipePair()
{
    Entity bottomPipe = _systemManager.CreateEntity();
    Entity topPipe = _systemManager.CreateEntity();

    PositionComponent * bottomPosition = _positionSystem.CreateComponent(bottomPipe);
    bottomPosition->Position.x += 230;
    bottomPosition->Position.y += 240;
    bottomPosition->Velocity.x = -65.0f;

    PositionComponent * topPosition = _positionSystem.CreateComponent(topPipe);
    topPosition->Position.x += 230;
    topPosition->Position.y += (240 - 200 - 40);
    topPosition->Velocity.x = -65.0f;

    _spriteSystem.CreateComponent(bottomPipe, "flappy-bottom-pipe", RenderPriority::Player, -1);
    _spriteSystem.CreateComponent(topPipe, "flappy-top-pipe", RenderPriority::Player, -1);
}
