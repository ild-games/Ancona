#include "PipeSpawnerSystem.hpp"
#include <Ancona/Framework/EntityFramework/UpdateStep.hpp>

using namespace ild;

PipeSpawnerSystem::PipeSpawnerSystem(SystemManager & manager)
    : UnorderedSystem(manager, UpdateStep::Update)
{
}

void PipeSpawnerSystem::Update(float delta)
{
    for(EntityComponentPair component : *this)
    {
        component.second->Update();
    }
}

PipeSpawnerComponent * PipeSpawnerSystem::CreateComponent(
        const Entity & entity,
        DrawableSystem & drawableSystem,
        PositionSystem & positionSystem,
        CollisionSystem & collisionSystem,
        SystemManager & systemManager,
        CollisionType pipeColType,
        CollisionType pointColType)
{
    auto comp = new PipeSpawnerComponent(
            drawableSystem, 
            positionSystem, 
            collisionSystem,
            systemManager, 
            pipeColType,
            pointColType);
    AttachComponent(entity, comp);
    return comp;
}
