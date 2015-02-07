#include <Ancona/Engine/Physics/BasePhysicsSystem.hpp>

using namespace ild;

BasePhysicsSystem::BasePhysicsSystem(SystemManager & manager)
    : UnorderedSystem<BasePhysicsComponent>(manager, UpdateStep::Update)
{

}
