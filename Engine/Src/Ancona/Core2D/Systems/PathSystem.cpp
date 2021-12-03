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

void PathComponent::Serialize(Archive &arc)
{
    arc(_vertices, "vertices");
    arc(_isLoop, "isLoop");
    arc(_cycleTime, "cycleTime");
}

void PathComponent::FetchDependencies(const Entity &entity)
{
}

float PathComponent::TimeForSegment(int segment)
{
    return _cycleTime * (DistanceForSegment(segment) / TotalDistance());
}

float PathComponent::DistanceForSegment(int segment)
{
    if (segment == (int)_vertices.size() - 1)
    {
        ILD_Assert(_isLoop, "Only loops should care about the last segment length because it connects the end points.")
    }

    Vector2f startVertex = _vertices[segment];
    Vector2f endVertex;
    if (segment == (int)_vertices.size() - 1)
    {
        endVertex = _vertices[0];
    }
    else
    {
        endVertex = _vertices[segment + 1];
    }
    return Math::Distance(startVertex, endVertex);
}

float PathComponent::TotalDistance()
{
    if (_isLoop)
    {
        float loopDistance = 0;
        for (int i = 0; i < (int)_vertices.size(); i++)
        {
            loopDistance += DistanceForSegment(i);
        }
        return loopDistance;
    }
    else
    {
        float backAndForthDistance = 0;
        for (int i = 0; i < (int)_vertices.size() - 1; i++)
        {
            backAndForthDistance += DistanceForSegment(i);
        }
        return backAndForthDistance * 2;
    }
}

/* System */
PathSystem::PathSystem(std::string name, SystemManager &manager) : UnorderedSystem(name, manager, UpdateStep::Update)
{
}

void PathSystem::Update(float delta)
{
    for (EntityComponentPair comp : *this)
    {
        comp.second->Update(delta);
    }
}

PathComponent *PathSystem::CreateComponent(const Entity &entity)
{
    PathComponent *comp = new PathComponent();
    AttachComponent(entity, comp);
    return comp;
}
