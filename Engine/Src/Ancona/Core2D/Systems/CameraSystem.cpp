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
        sf::Vector2f offset) :
    _view(sf::View(originalView)),
    _renderPriority(renderPriority),
    _scale(scale),
    _offset(offset),
    _drawableSystem(drawableSystem)
{
}

void CameraComponent::Update(float delta)
{
    MoveCamera();
}

void CameraComponent::Draw(sf::RenderWindow & window, float delta)
{
    window.setView(_view);
    for(DrawableComponent * drawable : _renderQueue)
    {
        drawable->Draw(window, delta);
    }
}

void CameraComponent::MoveCamera()
{
    if(_followPosition != nullptr)
    {
        _view.setCenter(
                _followPosition->position().x,
                _followPosition->position().y);
    }
    _view.setCenter(_view.getCenter() + _offset);
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
    _view.setCenter(0, 0);
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
