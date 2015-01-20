#include "PointSystem.hpp"
#include <Ancona/Engine/EntityFramework/UpdateStep.hpp>

using namespace ild;

PointSystem::PointSystem(SystemManager & manager)
    : UnorderedSystem(manager, UpdateStep::Update)
{
}

void PointSystem::Update(float delta) { }

PointComponent * PointSystem::CreateComponent(const Entity & entity)
{
    auto comp = new PointComponent();
    AttachComponent(entity, comp);
    return comp;
}
