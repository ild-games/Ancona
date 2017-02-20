#include "PathFollowerSystem.hpp"

using namespace ild;

/* Component */
PathFollowerComponent::PathFollowerComponent()
{
}

void PathFollowerComponent::Update(float delta)
{
    if (_pathComponent->vertices().size() == 0) {
        return;
    }
        
    if (_action->Done()) {
        StartNextPathSegment();
    }
}

void PathFollowerComponent::StartNextPathSegment()
{
    auto pathPosition = _pathPositionComponent->position();
    auto lastVertexIndex = _nextVertexIndex;
    _nextVertexIndex += _followDirection;
    
    if (!IsNextVertexValid()) {
        if (_pathComponent->isLoop()) {
            _nextVertexIndex = 0;
        } else {
            _nextVertexIndex -= _followDirection;
            _followDirection *= -1;
            _nextVertexIndex += _followDirection;
        }
    }
    float time = 0.0f;
    if (_followDirection == 1) {
        // get the time for the vertex we just came from if we're moving forward
        time = _pathComponent->TimeForSegment(lastVertexIndex);
    } else {
        // get the time for the vertex we're heading towards if we're moving backwards
        time = _pathComponent->TimeForSegment(_nextVertexIndex);
    }
    
    auto nextVertex = _pathComponent->vertices()[_nextVertexIndex];
    _action->
        ResetAge()->
        value(sf::Vector2f(pathPosition.x + nextVertex.x, pathPosition.y + nextVertex.y))->
        tween(time)->
        duration(time);
}

bool PathFollowerComponent::IsNextVertexValid() 
{
    return (
        _nextVertexIndex < _pathComponent->vertices().size() &&
        _nextVertexIndex > -1
    );
}

void PathFollowerComponent::Serialize(Archive & arc)
{
    std::string pathEntity;
    arc(pathEntity, "pathEntity");
    arc.entityUsingJsonKey(_pathEntity, "pathEntity");
    arc.system(_pathSystem, "path");
    arc.system(_positionSystem, "position");
    arc.system(_actionSystem, "action");
}

void PathFollowerComponent::FetchDependencies(const Entity &entity)
{
    _pathComponent = _pathSystem->at(_pathEntity);
    _pathPositionComponent = _positionSystem->at(_pathEntity);
    _actionComponent = _actionSystem->at(entity);
    _action = _actionComponent->actions().CreatePositionAction();
    _action->value(_pathPositionComponent->position())->duration(0);
    _entity = entity;
}

/* System */
PathFollowerSystem::PathFollowerSystem(
        std::string name,
        SystemManager &manager) :
    UnorderedSystem(name, manager, UpdateStep::Update)
{
}

void PathFollowerSystem::Update(float delta)
{
    for (EntityComponentPair comp : *this)
    {
        comp.second->Update(delta);
    }
}

PathFollowerComponent * PathFollowerSystem::CreateComponent(const Entity &entity)
{
    PathFollowerComponent * comp = new PathFollowerComponent();
    AttachComponent(entity, comp);
    return comp;
}
