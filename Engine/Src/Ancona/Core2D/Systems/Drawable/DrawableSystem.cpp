#include <jsoncpp/json/json.h>

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
    for(CameraComponent * camera : _cameras)
    {
        camera->Draw(_window, delta);
    }
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

DrawableComponent * DrawableSystem::CreateComponent(const Entity & entity)
{
    Assert(_defaultCamera != nullptr, "Default camera not set");
    return CreateComponent(entity, _defaultCamera);
}

DrawableComponent * DrawableSystem::CreateComponent(
        const Entity & entity,
        CameraComponent * camera)
{
    auto comp = new DrawableComponent(camera);

    if(alg::find(_cameras, camera) == _cameras.end())
    {
        _cameras.push_back(camera); 
    }

    AttachComponent(entity, comp);
    return comp;
}

void DrawableSystem::OnComponentRemove(Entity entity, DrawableComponent * component)
{
    std::vector<Drawable * > compDrawables = component->keylessDrawables();
    for(Drawable * drawable : compDrawables)
    {
        for(CameraComponent * camera : _cameras)
        {
            camera->RemoveDrawable(drawable);
        }
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
    AddCamera(defaultCamera);
}