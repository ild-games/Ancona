#include <Ancona/Core2D/Systems/Drawable/DrawableComponent.hpp>
#include <Ancona/Core2D/Systems/Drawable/DrawableSystem.hpp>

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
    if (!_drawables.count(key))
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
        AddDrawable(keyDrawable.first, keyDrawable.second.get());
        keyDrawable.second->FetchDependencies(entity);
    }
    _physicsComponent = _physicsSystem->at(entity);
    rotation(_serializedRotation);
    scale(_serializedScale);
}

void DrawableComponent::Serialize(Archive & arc)
{
    arc.entityUsingJsonKey(_camEntity, "camEntity");
    arc.system(_cameraSystem, "camera");
    arc.system(_drawableSystem, "drawable");
    arc.system(_physicsSystem, "physics");
    arc(_drawables, "drawables");
    arc(_serializedRotation, "rotation");
    arc(_serializedScale, "scale");
}

void DrawableComponent::UpdatePosition()
{
    sf::Vector2f newPosition = _physicsComponent->GetInfo().position();
    _dynamicTransform = sf::Transform();
    _dynamicTransform.translate(newPosition);
    _transform = _dynamicTransform.combine(_staticTransform);
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

void DrawableComponent::rotation(float newRotation)
{
    _staticTransform.rotate(-_rotation);
    _rotation = newRotation;
    _staticTransform.rotate(newRotation);
}

void DrawableComponent::scale(sf::Vector2f newScale)
{
    _staticTransform.scale(
            1 / _scale.x,
            1 / _scale.y);
    _scale = newScale;
    _staticTransform.scale(
            newScale.x,
            newScale.y);
}

sf::Vector2u DrawableComponent::size()
{
    float maxWidth = 0, maxHeight = 0, curWidth = 0, curHeight = 0;
    for (auto & drawable : _drawables)
    {
        sf::Vector2u drawableSize = drawable.second->size();
        curWidth = drawable.second->positionOffset().x + drawableSize.x;
        curHeight = drawable.second->positionOffset().y + drawableSize.y;
        maxWidth = std::max(maxWidth, curWidth);
        maxHeight = std::max(maxHeight, curHeight);
    }
    return sf::Vector2u(maxWidth, maxHeight);
}

