#include <Ancona/Core2D/Systems/Drawable/DrawableSystem.hpp>
#include <Ancona/Framework/EntityFramework/UpdateStep.hpp>
#include <Ancona/Util/Algorithm.hpp>

using namespace ild;

DrawableSystem::DrawableSystem(
        std::string systemName,
        sf::RenderWindow & window,
        SystemManager & systemManager) :
    UnorderedSystem(systemName, systemManager, UpdateStep::Draw),
    _window(window)
{
}

void DrawableSystem::Update(float delta)
{
    for (CameraComponent * camera : _cameras)
    {
        camera->Draw(_window, delta);
    }
    _window.setView(_defaultCamera->view());
}

void DrawableSystem::AddCamera(CameraComponent * camera)
{
    _cameras.push_back(camera);
    alg::sort(_cameras,
            [](CameraComponent * lhs, CameraComponent * rhs)
            {
                return lhs->renderPriority() < rhs->renderPriority();
            });
}

void DrawableSystem::RemoveCamera(CameraComponent * camera)
{
    _cameras.erase(std::remove(_cameras.begin(), _cameras.end(), camera), _cameras.end());
}

DrawableComponent * DrawableSystem::CreateComponent(
        const Entity & entity,
        std::unique_ptr<Drawable> topDrawable,
        PositionSystem * position)
{
    Assert(_defaultCamera != nullptr, "Default camera not set");
    return CreateComponent(entity, std::move(topDrawable), position, _defaultCamera);
}

DrawableComponent * DrawableSystem::CreateComponent(
        const Entity & entity,
        std::unique_ptr<Drawable> topDrawable,
        PositionSystem * position,
        CameraComponent * camera)
{
    auto comp = new DrawableComponent(std::move(topDrawable), this, position, camera);

    if(alg::find(_cameras, camera) == _cameras.end())
    {
        _cameras.push_back(camera);
    }

    AttachComponent(entity, comp);
    return comp;
}

void DrawableSystem::OnComponentRemove(Entity entity, DrawableComponent * component)
{
    for(CameraComponent * camera : _cameras)
    {
        camera->RemoveDrawableComponent(component);
    }
}

/* getters and setters */
void DrawableSystem::defaultCamera(CameraComponent *defaultCamera)
{
    if(_defaultCamera != nullptr)
    {
        RemoveCamera(_defaultCamera);
    }
    _defaultCamera = defaultCamera;
}
