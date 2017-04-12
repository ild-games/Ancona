#include "PathFollowerSystem.hpp"

using namespace ild;

/* Component */
PathFollowerComponent::PathFollowerComponent() {
}

void PathFollowerComponent::Update(float delta) {
    if (_pathComponent->vertices().size() == 0) {
        return;
    }

    if (_action->Done()) {
        StartNextPathSegment();
    }
}

void PathFollowerComponent::StartNextPathSegment() {
    auto lastVertexIndex = _nextVertexIndex;

    _nextVertexIndex += _followDirection;
    if (IsPathDone()) {
        _nextVertexIndex = NewVertexIndexAfterPathEnd();
        if (!_pathComponent->isLoop()) {
            ChangeDirection();
        }
    }

    auto time = NextSegmentTime(lastVertexIndex, _nextVertexIndex);
    _action->
        ResetAge()->
        value(NextSegmentDistance())->
        tween(time)->
        duration(time);
}

int PathFollowerComponent::NewVertexIndexAfterPathEnd() {
    if (_pathComponent->isLoop()) {
        return 0;
    } else {
        return _nextVertexIndex - _followDirection + (_followDirection * -1);
    }
}

float PathFollowerComponent::NextSegmentTime(int lastVertexIndex, int nextVertexIndex) {
    if (_followDirection == 1) {
        // get the time for the vertex we just came from if we're moving forward
        return _pathComponent->TimeForSegment(lastVertexIndex);
    } else {
        // get the time for the vertex we're heading towards if we're moving backwards
        return _pathComponent->TimeForSegment(nextVertexIndex);
    }
}

sf::Vector2f PathFollowerComponent::NextSegmentDistance() {
    auto nextVertex = _pathComponent->vertices()[_nextVertexIndex];
    return sf::Vector2f(
        _pathPositionComponent->position().x + nextVertex.x,
        _pathPositionComponent->position().y + nextVertex.y);
}

void PathFollowerComponent::ChangeDirection() {
    _followDirection *= -1;
}

bool PathFollowerComponent::IsPathDone() {
    return (
        _nextVertexIndex >= _pathComponent->vertices().size() ||
        _nextVertexIndex < 0
    );
}

void PathFollowerComponent::Serialize(Archive & arc) {
    arc.entityUsingJsonKey(_pathEntity, "pathEntity");
    arc.system(_pathSystem, "path");
    arc.system(_positionSystem, "position");
    arc.system(_actionSystem, "action");
}

void PathFollowerComponent::FetchDependencies(const Entity &entity) {
    _pathComponent = _pathSystem->at(_pathEntity);
    _pathPositionComponent = _positionSystem->at(_pathEntity);
    _actionComponent = _actionSystem->at(entity);
    _action = _actionComponent->actions().CreatePositionAction();
    auto firstVertex = (_pathComponent->vertices().size() > 0) ? _pathComponent->vertices()[0] : sf::Vector2f(0.0f, 0.0f);
    _action->value(_pathPositionComponent->position() + firstVertex)->duration(0);
    _entity = entity;
}

/* System */
PathFollowerSystem::PathFollowerSystem(
        std::string name,
        SystemManager &manager) :
    UnorderedSystem(name, manager, UpdateStep::Update) {
}

void PathFollowerSystem::Update(float delta) {
    for (EntityComponentPair comp : *this) {
        comp.second->Update(delta);
    }
}

PathFollowerComponent * PathFollowerSystem::CreateComponent(const Entity &entity) {
    PathFollowerComponent * comp = new PathFollowerComponent();
    AttachComponent(entity, comp);
    return comp;
}
