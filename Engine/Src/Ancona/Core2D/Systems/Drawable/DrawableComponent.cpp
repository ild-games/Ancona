#include <cmath>

#include <Ancona/Core2D/Systems/Drawable/DrawableComponent.hpp>
#include <Ancona/Core2D/Systems/Drawable/DrawableSystem.hpp>
#include <Ancona/Core2D/Systems/Position/PositionSystem.hpp>
#include <Ancona/Util/Math.hpp>

using namespace ild;

DrawableComponent::DrawableComponent() { }

DrawableComponent::DrawableComponent(
        std::unique_ptr<Drawable> topDrawable,
        DrawableSystem * drawableSystem,
        PositionSystem * positionSystem,
        CameraComponent * cameraComponent) :
    _topDrawable(std::move(topDrawable)),
    _camera(cameraComponent),
    _positionSystem(positionSystem),
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
    transform.translate(std::round(_positionComponent->position().x), std::round(_positionComponent->position().y));
    _topDrawable->Draw(window, transform, delta);
}


void DrawableComponent::PostDrawUpdate(float delta)
{
    _topDrawable->PostDrawUpdate(delta);
}

Box2 DrawableComponent::BoundingBox()
{
    return Box2(
        _topDrawable->position(_positionComponent->position()),
        _topDrawable->size(),
        _topDrawable->anchor(),
        Math::DegreesToRadians(_topDrawable->rotation()));
}

void DrawableComponent::FetchDependencies(const Entity & entity)
{
    if(_camEntity == nullentity)
    {
        _camera = _drawableSystem->defaultCamera();
        ILD_Assert(_drawableSystem->defaultCamera() != nullptr, "Default camera not set");
    }
    else
    {
        _camera = (*_cameraSystem)[_camEntity];
    }
    _camera->AddDrawableComponent(this);
    _positionComponent = _positionSystem->at(entity);
    _topDrawable->FetchDependencies(entity);
}

void DrawableComponent::Serialize(Archive & arc)
{
    arc.entityUsingJsonKey(_camEntity, "camEntity");
    arc.system(_cameraSystem, "camera");
    arc.system(_drawableSystem, "drawable");
    arc.system(_positionSystem, "position");
    arc(_topDrawable, "topDrawable");
}
