#include <Ancona/Core2D/Systems/Physics/BasePhysicsSystem.hpp>

REGISTER_POLYMORPHIC_SERIALIZER(ild::BasePhysicsComponent);

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

void BasePhysicsComponent::Serialize(Archive & arc)
{
    arc(_position, "info");
}
