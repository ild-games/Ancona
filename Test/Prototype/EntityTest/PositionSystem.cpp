#include "PositionSystem.hpp"

PositionSystem::PositionSystem(SystemManager & manager) :
    UnorderedSystem<PositionComponent>(manager, UpdateStepEnum::Update)
{

}

void PositionSystem::Update(float delta)
{

}
