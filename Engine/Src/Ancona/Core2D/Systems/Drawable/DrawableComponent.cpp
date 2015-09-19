#include <Ancona/Core2D/Systems/Drawable/DrawableComponent.hpp>
#include <Ancona/Core2D/Systems/Drawable/DrawableSystem.hpp>
#include <Ancona/Platformer/Physics/PlatformPhysicsSystem.hpp>

using namespace ild;

DrawableComponent::DrawableComponent() { }

DrawableComponent::DrawableComponent(
        Drawable * topDrawable,
        DrawableSystem * drawableSystem,
        BasePhysicsSystem * physicsSystem,
        CameraComponent * cameraComponent) :
    _topDrawable(topDrawable),
    _camera(cameraComponent),
    _physicsSystem(physicsSystem),
    _drawableSystem(drawableSystem)
{
}


Drawable * DrawableComponent::GetDrawable(const std::string & key)
{
    return _topDrawable->FindDrawable(key);
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
