#include <Ancona/Engine/Core/Systems/Physics/BasePhysicsSystem.hpp>

using namespace ild;

BasePhysicsSystem::BasePhysicsSystem(
        std::string systemName,
        SystemManager & manager) : 
    UnorderedSystem<BasePhysicsComponent>(
            systemName, 
            manager, 
            UpdateStep::Update)
{

}
