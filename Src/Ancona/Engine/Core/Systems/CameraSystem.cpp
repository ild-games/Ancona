#include <Ancona/Engine/Core/Systems/CameraSystem.hpp>

using namespace ild;

/* Component */
CameraComponent::CameraComponent(
        const sf::View & originalView,
        BasePhysicsComponent & cameraPhysics,
        int renderPriority,
        float scale) :
    _cameraPhysics(cameraPhysics),
    _view(sf::View(originalView)),
    _renderPriority(renderPriority)
{
    _view.zoom(scale);
}

void CameraComponent::Update(float delta)
{
    MoveCamera();
}

void CameraComponent::Draw(sf::RenderWindow & window, float delta)
{
    window.setView(_view);
    for(Drawable * drawable : _renderQueue)
    {
        drawable->Draw(window, delta);
    }
}

void CameraComponent::MoveCamera()
{
    float x = 0, y = 0;
    if(_followPhysics != nullptr)
    {
        x = _followPhysics->GetInfo().GetPosition().x;
        y = _followPhysics->GetInfo().GetPosition().y;
    }
    _view.setCenter(x, y);
}

void CameraComponent::AddDrawable(Drawable * drawable)
{
    _renderQueue.push_back(drawable);
    std::sort(
            _renderQueue.begin(),
            _renderQueue.end(),
            [](Drawable * lhs, Drawable * rhs)
            {
                return lhs->GetRenderPriority() < rhs->GetRenderPriority();
            });
}

void CameraComponent::RemoveDrawable(Drawable * drawable)
{
    _renderQueue.erase(std::remove(_renderQueue.begin(), _renderQueue.end(), drawable), _renderQueue.end());
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
        const sf::View & originalView,
        BasePhysicsComponent & cameraPhysics,
        int renderPriority,
        float scale)
{
    CameraComponent * comp = new CameraComponent(
            originalView,
            cameraPhysics,
            renderPriority,
            scale);
    AttachComponent(entity, comp);
    return comp;
}
