#include "PipeSpawnerComponent.hpp"

using namespace ild;

#include <iostream>
#include <random>

PipeSpawnerComponent::PipeSpawnerComponent(
        SpriteSystem & spriteSystem,
        PositionSystem & positionSystem,
        CollisionSystem & collisionSystem,
        SystemManager & systemManager,
        CollisionType pipeColType)
    : _spriteSystem(spriteSystem), 
      _positionSystem(positionSystem),
      _collisionSystem(collisionSystem),
      _systemManager(systemManager),
      _randDistribution(MIN_Y_BOTTOM_PIPE, MAX_Y_BOTTOM_PIPE),
      _pipeColType(pipeColType)
{
    _clock = new sf::Clock();
}

void PipeSpawnerComponent::Update()
{    
    if(TimeToSpawn())
    {
        SpawnPipePair();
        _clock->restart();
    }
    if(TimeToDespawn())
    {
        DespawnPipePair();
    }
}

bool PipeSpawnerComponent::TimeToSpawn()
{
    return _clock->getElapsedTime().asSeconds() > SECONDS_BETWEEN_SPAWN;
}

bool PipeSpawnerComponent::TimeToDespawn()
{
    return !_currentPipes.empty() && _positionSystem[_currentPipes[0]]->Position.x < -100.0f;
}

void PipeSpawnerComponent::SpawnPipePair()
{
    Entity bottomPipe = CreatePipe(
            230, 
            PickBottomPipeY(), 
            false);
    Entity topPipe = CreatePipe(
            230, 
            (_positionSystem[bottomPipe]->Position.y - 200 - GAP_HEIGHT), 
            true);
}

void PipeSpawnerComponent::DespawnPipePair()
{
    Entity pipe1 = _currentPipes[0];
    Entity pipe2 = _currentPipes[1];
    _systemManager.DeleteEntity(pipe1);
    _systemManager.DeleteEntity(pipe2);
    _currentPipes.erase(_currentPipes.begin());
    _currentPipes.erase(_currentPipes.begin());
}

Entity PipeSpawnerComponent::CreatePipe(float x, float y, bool topPipe)
{
    Entity pipe = _systemManager.CreateEntity();     
    PositionComponent * pos = _positionSystem.CreateComponent(pipe);
    pos->Position.x = x;
    pos->Position.y = y;
    pos->Velocity.x = PIPE_SPEED;
    _spriteSystem.CreateComponent(pipe, SpriteToUse(topPipe), RenderPriority::Player, -2);
    _collisionSystem.CreateComponent(pipe, sf::Vector3f(24.0f, 200.0f, 0),_pipeColType);
    _currentPipes.push_back(topPipe);
    return pipe;
}

std::string PipeSpawnerComponent::SpriteToUse(bool topPipe)
{
    if(topPipe)
    {
        return "flappy-top-pipe";
    } 
    else 
    {
        return "flappy-bottom-pipe";
    }
}

float PipeSpawnerComponent::PickBottomPipeY()
{
    return _randDistribution(_mtEngine);
}
