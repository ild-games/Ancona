#include <Ancona/Util/Math.hpp>

#include "PathSystem.hpp"

using namespace ild;

/* Component */
PathComponent::PathComponent()
{
}

void PathComponent::Update(float delta)
{
}

void PathComponent::Serialize(Archive & arc)
{
    arc(_vertices, "vertices");
    arc(_isLoop, "isLoop");
    arc(_time, "time");
}

void PathComponent::FetchDependencies(const Entity &entity)
{
}

float PathComponent::TimeForSegment(int segment) 
{
    return _time * (DistanceForSegment(segment) / TotalDistance());
}

float PathComponent::DistanceForSegment(int segment)
{
    if (segment == _vertices.size() - 1) {
        Assert(_isLoop, "Only loops should care about the last segment length because it connects the end points.")
    }

    sf::Vector2f startVertex = _vertices[segment];
    sf::Vector2f endVertex;
    if (segment == _vertices.size() - 1) {
        endVertex = _vertices[0];
    } else {
        endVertex = _vertices[segment + 1];
    }
    return Math::DistanceBetween(startVertex, endVertex);
}

float PathComponent::TotalDistance()
{
    if (_isLoop) {
        float totalDistance = 0;
        for (int i = 0; i < _vertices.size(); i++) {
            totalDistance += DistanceForSegment(i);
        }
        return totalDistance;
    } else {
        float totalDistance = 0;
        for (int i = 0; i < _vertices.size() - 1; i++) {
            totalDistance += DistanceForSegment(i);
        }
        return totalDistance * 2;
    }
}

/* System */
PathSystem::PathSystem(
        std::string name,
        SystemManager &manager) :
    UnorderedSystem(name, manager, UpdateStep::Update)
{
}

void PathSystem::Update(float delta)
{
    for (EntityComponentPair comp : *this)
    {
        comp.second->Update(delta);
    }
}

PathComponent * PathSystem::CreateComponent(const Entity &entity)
{
    PathComponent * comp = new PathComponent();
    AttachComponent(entity, comp);
    return comp;
}
