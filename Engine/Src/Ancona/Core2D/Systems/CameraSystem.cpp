#include <cmath>

#include <Ancona/Util/Assert.hpp>
#include <Ancona/Core2D/Systems/CameraSystem.hpp>
#include <Ancona/Core2D/Systems/Drawable/DrawableSystem.hpp>
#include <Ancona/System/Log.hpp>


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
    _view.setCenter(
        std::round(effectivePosition.x) + ((_screenManager->windowWidth() / _view.getSize().x) - 1.0f),
        std::round(effectivePosition.y) + ((_screenManager->windowHeight() / _view.getSize().y) - 1.0f));
}

void CameraComponent::Draw(sf::RenderWindow & window, float delta)
{
    Box2 cameraPosition(
        sf::Vector2f(_view.getCenter().x - (_view.getSize().x), _view.getCenter().y - (_view.getSize().y)),
        sf::Vector2f(_view.getSize().x * 2, _view.getSize().y * 2),
        sf::Vector2f(),
        _view.getRotation());

    window.setView(_view);

    alg::sort(
        _renderQueue,
        [](DrawableComponent * lhs, DrawableComponent * rhs)
    {
        return lhs->topDrawable()->renderPriority() < rhs->topDrawable()->renderPriority();
    });

    for(DrawableComponent * drawable : _renderQueue)
    {
        auto drawableBox = drawable->BoundingBox();
        if (cameraPosition.Intersects(drawableBox))
        {
            drawable->Draw(window, delta);
        }
        drawable->PostDrawUpdate(delta);
    }
}

sf::Vector2f CameraComponent::GetEffectiveCenter()
{
    sf::Vector2f effectivePosition = sf::Vector2f(
        _view.getCenter().x - ((_screenManager->windowWidth() / _view.getSize().x) - 1.0f),
        _view.getCenter().y - ((_screenManager->windowHeight() / _view.getSize().y) - 1.0f));
    if (_followPosition != nullptr)
    {
        effectivePosition = _followPosition->position();
    }

    effectivePosition.x = std::max(std::min(effectivePosition.x, _upperBounds.x), _lowerBounds.x);
    effectivePosition.y = std::max(std::min(effectivePosition.y, _upperBounds.y), _lowerBounds.y);

    effectivePosition += _offset;

    return sf::Vector2f(effectivePosition.x, effectivePosition.y);
}

void CameraComponent::AddDrawableComponent(DrawableComponent * drawable)
{
	Assert(!alg::contains(_renderQueue, drawable), "Can't add the same drawable twice.");
    _renderQueue.push_back(drawable);
}

void CameraComponent::RemoveDrawableComponent(DrawableComponent * drawable)
{
    if (std::find(_renderQueue.begin(), _renderQueue.end(), drawable) != _renderQueue.end()) {
        _renderQueue.erase(alg::remove(_renderQueue, drawable));
    }
}

void CameraComponent::FetchDependencies(const Entity & entity)
{
    if(_follows != nullentity)
    {
        _followPosition = (*_positionSystem)[_follows];
    }
    _view.setSize(_size);
    _view.setCenter((int) (_size.x / 2), (int) (_size.y / 2));
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
    arc.screenManager(_screenManager);
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
    for (EntityComponentPair comp : *this)
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
