#include <Ancona/Engine/Core/Systems/Drawable/DrawableSystem.hpp>
#include <Ancona/Engine/EntityFramework/UpdateStep.hpp>

#include <algorithm>

using namespace ild;


DrawableSystem::DrawableSystem(
        sf::RenderWindow & window, 
        SystemManager & systemManager, 
        BasePhysicsSystem & physicsSystem) : 
    UnorderedSystem(systemManager, UpdateStep::Draw), 
    _window(window), 
    _physicsSystem(physicsSystem)
{
}

void DrawableSystem::Update(float delta)
{
    for(CameraComponent * camera : _cameras)
    {
        camera->Draw(_window, delta);
    }
}

void DrawableSystem::AddCamera(CameraComponent * camera)
{
    _cameras.push_back(camera);
    std::sort(
            _cameras.begin(),
            _cameras.end(), 
            [](CameraComponent * lhs, CameraComponent * rhs)
            {
                return lhs->GetRenderPriority() < rhs->GetRenderPriority();
            });
}

void DrawableSystem::RemoveCamera(CameraComponent * camera)
{
    _cameras.erase(std::remove(_cameras.begin(), _cameras.end(), camera), _cameras.end());
}

DrawableComponent * DrawableSystem::CreateComponent(
        const Entity & entity,
        CameraComponent & camera)
{
    auto comp = new DrawableComponent(
            *this,
            camera);

    // if the camera isn't already in the cameras vector, add it now
    if(std::find(_cameras.begin(), _cameras.end(), &camera) == _cameras.end())
    {
        _cameras.push_back(&camera); 
    }

    AttachComponent(entity, comp);
    return comp;
}

void DrawableSystem::OnComponentRemove(Entity entity, DrawableComponent * component)
{
    std::vector<Drawable * > compDrawables = component->GetDrawables();
    for(Drawable * drawable : compDrawables)
    {
        for(CameraComponent * camera : _cameras)
        {
            camera->RemoveDrawable(drawable);
        }
    }
}

