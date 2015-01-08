#include "PipeSpawnerSystem.hpp"
#include <Ancona/Engine/EntityFramework/UpdateStep.hpp>

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
        SpriteSystem & spriteSystem,
        PositionSystem & positionSystem,
        CollisionSystem & collisionSystem,
        SystemManager & systemManager,
        CollisionType pipeColType,
        CollisionType pointColType)
{
    auto comp = new PipeSpawnerComponent(
            spriteSystem, 
            positionSystem, 
            collisionSystem,
            systemManager, 
            pipeColType,
            pointColType);
    AttachComponent(entity, comp);
    return comp;
}
