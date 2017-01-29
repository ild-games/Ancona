#include <Ancona/Core2D/Systems/CameraSystem.hpp>
#include <Ancona/Core2D/Systems/Drawable/DrawableSystem.hpp>

using namespace ild;

/* Component */
CameraComponent::CameraComponent() : _offset(sf::Vector2f(0, 0)) { }

CameraComponent::CameraComponent(
        const sf::View & originalView,
        int renderPriority,
        DrawableSystem * drawableSystem,
        float scale,
        sf::Vector2f offset,
        sf::Vector2f upperBounds,
        sf::Vector2f lowerBounds) :
    _view(sf::View(originalView)),
    _renderPriority(renderPriority),
    _scale(scale),
    _offset(offset),
    _lowerBounds(lowerBounds),
    _upperBounds(upperBounds),
    _drawableSystem(drawableSystem)
{
}

void CameraComponent::Update(float delta)
{
    auto effectivePosition = GetEffectiveCenter();
    _view.setCenter(round(effectivePosition.x), round(effectivePosition.y));
}

void CameraComponent::Draw(sf::RenderWindow & window, float delta)
{
    Box2 cameraPosition(_view.getCenter(), _view.getSize(), _view.getRotation());

    window.setView(_view);
    for(DrawableComponent * drawable : _renderQueue)
    {
        auto drawableBox = drawable->BoundingBox();
        if (cameraPosition.Intersects(drawableBox))
        {
            drawable->Draw(window, delta);
        }
    }
}

sf::Vector2f CameraComponent::GetEffectiveCenter() 
{
    sf::Vector2f effectivePosition = _view.getCenter();
    if (_followPosition != nullptr)
    {
        effectivePosition = _followPosition->position();
    }

    effectivePosition.x = std::max(std::min(effectivePosition.x, _upperBounds.x), _lowerBounds.x);
    effectivePosition.y = std::max(std::min(effectivePosition.y, _upperBounds.y), _lowerBounds.y);

    effectivePosition += _offset;

    return effectivePosition;
}

void CameraComponent::AddDrawableComponent(DrawableComponent * drawable)
{
    if(!alg::contains(_renderQueue, drawable))
    {
        _renderQueue.push_back(drawable);
        alg::sort(
                _renderQueue,
                [](DrawableComponent * lhs, DrawableComponent * rhs)
                {
                    return lhs->topDrawable()->renderPriority() < rhs->topDrawable()->renderPriority();
                });
    }
}

void CameraComponent::RemoveDrawableComponent(DrawableComponent * drawable)
{
    _renderQueue.erase(alg::remove(_renderQueue, drawable));
}

void CameraComponent::FetchDependencies(const Entity & entity)
{
    if(_follows != nullentity)
    {
        _followPosition = (*_positionSystem)[_follows];
    }
    _view.setSize(_size);
    _view.setCenter(_size.x / 2, _size.y / 2);
    scale(_originalScale);
    _drawableSystem->AddCamera(this);
    if(_default)
    {
        _drawableSystem->defaultCamera(this);
    }
}

void CameraComponent::Serialize(Archive & arc)
{
    arc(_renderPriority, "renderPriority");
    arc(_originalScale, "scale");
    arc(_default, "default");
    arc(_size, "size");
    arc(_offset, "offset");
    arc(_lowerBounds, "lowerBounds");
    arc(_upperBounds, "upperBounds");
    arc.entityUsingJsonKey(_follows, "follows");
    arc.system(_positionSystem, "position");
    arc.system(_drawableSystem, "drawable");
}

void CameraComponent::follows(Entity follows)
{
    _follows = follows;
    _followPosition = _positionSystem->at(follows);
}

/* getters and setters */
void CameraComponent::scale(float scale)
{
    Assert(scale != float(0), "Scale cannot be 0");
    _view.zoom(1 / _scale);
    _scale = scale;
    _view.zoom(_scale);
}

/* System */
CameraSystem::CameraSystem(
        std::string name,
        SystemManager & manager) :
    UnorderedSystem(name, manager, UpdateStep::Draw)
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
        int renderPriority,
        DrawableSystem * drawableSystem,
        float scale)
{
    CameraComponent * comp = new CameraComponent(
            originalView,
            renderPriority,
            drawableSystem,
            scale);
    AttachComponent(entity, comp);
    return comp;
}
