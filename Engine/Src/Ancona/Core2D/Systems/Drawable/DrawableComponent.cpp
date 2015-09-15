#include <Ancona/Core2D/Systems/Drawable/DrawableComponent.hpp>
#include <Ancona/Core2D/Systems/Drawable/DrawableSystem.hpp>

using namespace ild;

DrawableComponent::DrawableComponent() { }

DrawableComponent::DrawableComponent(CameraComponent * cameraComponent) :
    _camera(cameraComponent)
{
}

void DrawableComponent::AddCachedDrawable(const std::string key, Drawable *drawable)
{
    if (!_drawables.count(key))
    {
        _drawables[key] = drawable;
    }
}

void DrawableComponent::RemoveCachedDrawable(const std::string key)
{
    if (_drawables.count(key))
    {
        _drawables.erase(key);
    }
}

Drawable * DrawableComponent::GetCachedDrawable(const std::string key)
{
    return _drawables[key];
}


void DrawableComponent::Draw(sf::RenderWindow &window, float delta)
{
    sf::Transform transform;
    transform.translate(_physicsComponent->GetInfo().position());
    _topDrawable->Draw(window, transform, delta);
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
    _camera->AddDrawableComponent(this);
    _physicsComponent = _physicsSystem->at(entity);
    _topDrawable->FetchDependencies(entity);
}

void DrawableComponent::Serialize(Archive & arc)
{
    arc.entityUsingJsonKey(_camEntity, "camEntity");
    arc.system(_cameraSystem, "camera");
    arc.system(_drawableSystem, "drawable");
    arc.system(_physicsSystem, "physics");
    arc(_topDrawable, "topDrawable");
}
