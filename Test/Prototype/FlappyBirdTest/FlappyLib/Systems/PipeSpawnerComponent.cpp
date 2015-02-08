#include "PipeSpawnerComponent.hpp"

using namespace ild;

#include <iostream>
#include <random>

PipeSpawnerComponent::PipeSpawnerComponent(
        DrawableSystem & drawableSystem,
        PositionSystem & positionSystem,
        CollisionSystem & collisionSystem,
        SystemManager & systemManager,
        CollisionType pipeColType,
        CollisionType pointColType) : 
    _drawableSystem(drawableSystem), 
    _positionSystem(positionSystem),
    _collisionSystem(collisionSystem),
    _systemManager(systemManager),
    _mtEngine(time(NULL)),
    _randDistribution(MIN_Y_BOTTOM_PIPE, MAX_Y_BOTTOM_PIPE),
    _pipeColType(pipeColType),
    _pointColType(pointColType),
    _stopSpawning(true)
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

void PipeSpawnerComponent::StopMovingPipes()
{
    for(Entity pipe : _currentPipes)
    {
        _positionSystem[pipe]->Velocity.x = 0;
    }
    for(Entity point : _points)
    {
        _positionSystem[point]->Velocity.x = 0;
    }
    _stopSpawning = true;
}

bool PipeSpawnerComponent::TimeToSpawn()
{
    return _clock->getElapsedTime().asSeconds() > SECONDS_BETWEEN_SPAWN && !_stopSpawning;
}

bool PipeSpawnerComponent::TimeToDespawn()
{
    return !_currentPipes.empty() && _positionSystem[_currentPipes[0]]->Position.x < -100.0f;
}

void PipeSpawnerComponent::SpawnPipePair()
{
    Entity bottomPipe = CreatePipe(
            X_PIPE, 
            PickBottomPipeY(), 
            false);
    int topPipeY = _positionSystem[bottomPipe]->Position.y - 
        _drawableSystem[bottomPipe]->GetDrawable("pipe-sprite")->GetSize().y - 
        GAP_HEIGHT;
    Entity topPipe = CreatePipe(
            X_PIPE, 
            topPipeY,
            true);
    CreatePoint(bottomPipe);
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

void PipeSpawnerComponent::DespawnPoint(Entity point)
{
    _systemManager.QueueDelete(point);
    _points.erase(std::remove(_points.begin(), _points.end(), point), _points.end());
}

Entity PipeSpawnerComponent::CreatePipe(float x, float y, bool isTopPipe)
{
    Entity pipe = _systemManager.CreateEntity();     
    PositionComponent * pos = _positionSystem.CreateComponent(pipe);
    pos->Position.x = x;
    pos->Position.y = y;
    pos->Velocity.x = PIPE_SPEED;
    DrawableComponent * drawable = _drawableSystem.CreateComponent(pipe);
    drawable->AddDrawable(
            "pipe-sprite",
            new SpriteDrawable(
                *pos,
                SpriteToUse(isTopPipe),
                RenderPriority::Player,
                -2));
    _collisionSystem.CreateComponent(pipe, sf::Vector3f(24.0f, 200.0f, 0),_pipeColType);
    _currentPipes.push_back(pipe);

    return pipe;
}

void PipeSpawnerComponent::CreatePoint(Entity bottomPipe)
{
    Entity point = _systemManager.CreateEntity();
    PositionComponent * pos = _positionSystem.CreateComponent(point);
    pos->Position.x = X_PIPE + 10;
    pos->Position.y = _positionSystem[bottomPipe]->Position.y - 
        (_drawableSystem[bottomPipe]->GetDrawable("pipe-sprite")->GetSize().y / 2) - 
        (GAP_HEIGHT / 2); 
    pos->Velocity.x = PIPE_SPEED;
    _collisionSystem.CreateComponent(point, sf::Vector3f(10.0f, GAP_HEIGHT, 0), _pointColType);
    _points.push_back(point);
}

std::string PipeSpawnerComponent::SpriteToUse(bool isTopPipe)
{
    if(isTopPipe)
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

void PipeSpawnerComponent::SetStopSpawning(bool stopSpawning)
{
    _stopSpawning = stopSpawning;
    _clock->restart();
}
