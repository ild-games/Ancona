#include <Ancona/Engine/Core/Systems/Drawable/DrawableComponent.hpp>
#include <Ancona/Engine/Core/Systems/Drawable/DrawableSystem.hpp>

using namespace ild;

DrawableComponent::DrawableComponent() { }

DrawableComponent::DrawableComponent(CameraComponent * cameraComponent) :
    _camera(cameraComponent)
{
}

void DrawableComponent::AddDrawable(
        const std::string key,
        Drawable * drawable)
{
    auto keyDrawablePair = _drawables.find(key);
    if (keyDrawablePair == _drawables.end() || keyDrawablePair->second.get() != drawable)
    {
        _drawables[key] = std::unique_ptr<Drawable>(drawable);
    }
    _camera->AddDrawable(drawable);
}

void DrawableComponent::RemoveDrawable(const std::string key)
{
    _camera->RemoveDrawable(_drawables[key].get());
    _drawables.erase(key);
}

void DrawableComponent::FetchDependencies(const Entity & entity)
{
    if(_camEntity == nullentity)
    {
        _camera = _drawableSystem->defaultCamera();
    }
    else
    {
        _camera = (*_cameraSystem)[_camEntity];
    }
    for (auto & keyDrawable : _drawables)
    {
        keyDrawable.second->FetchDependencies(entity);
    }
}

void DrawableComponent::Serialize(Archive & arc)
{
    arc.entityUsingJsonKey(_camEntity, "cam-entity");
    arc.system(_cameraSystem, "camera");
    arc.system(_drawableSystem, "drawable");
    arc(_drawables, "drawables");
}

/* getters and setters */
std::vector<Drawable *> DrawableComponent::keylessDrawables()
{
    std::vector<Drawable *> toReturn;
    for(auto it = _drawables.begin(); it != _drawables.end(); ++it)
    {
        toReturn.push_back(it->second.get());
    }
    return toReturn;
}
