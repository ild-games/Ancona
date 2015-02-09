#include <Ancona/Engine/Core/Systems/CameraSystem.hpp>

using namespace ild;

/* Component */
CameraComponent::CameraComponent(
        PositionComponent & cameraPosition,
        PositionComponent & followPosition) :
    _cameraPosition(cameraPosition),
    _followPosition(followPosition)
{
    _view = new sf::View();
}

void CameraComponent::Update(float delta)
{
}

/* System */
CameraSystem::CameraSystem(
        SystemManager & manager) :
    UnorderedSystem(manager, UpdateStep::Update)
{
}

void CameraSystem::Update(float delta)
{
    for(EntityComponentPair comp : *this)
    {
        comp.second->Update(delta);
    }
}

CameraComponent * CameraSystem::CreateComponent(
        const Entity & entity,
        PositionComponent & cameraPosition,
        PositionComponent & followPosition)
{
    CameraComponent * comp = new CameraComponent(
            cameraPosition,
            followPosition);
    AttachComponent(entity, comp);
    return comp;
}
