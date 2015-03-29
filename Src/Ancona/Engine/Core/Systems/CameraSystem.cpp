#include <Ancona/Engine/Core/Systems/CameraSystem.hpp>
#include <Ancona/Engine/Core/Systems/Drawable/DrawableSystem.hpp>
#include <Ancona/Engine/Core/Systems/Physics/PlatformPhysicsSystem.hpp>

using namespace ild;

/* Component */
CameraComponent::CameraComponent() { }

CameraComponent::CameraComponent(
        const sf::View & originalView,
        int renderPriority,
        float scale) :
    _view(sf::View(originalView)),
    _renderPriority(renderPriority),
    _scale(scale)
{
    _view.zoom(scale);
}

void CameraComponent::Update(float delta)
{
    MoveCamera();
}

void CameraComponent::Draw(sf::RenderWindow & window, float delta)
{
    window.setView(_view);
    for(Drawable * drawable : _renderQueue)
    {
        drawable->Draw(window, delta);
    }
}

void CameraComponent::MoveCamera()
{
    if(_followPhysics != nullptr)
    {
        _view.setCenter(
            _followPhysics->GetInfo().GetPosition().x,
            _followPhysics->GetInfo().GetPosition().y);
    }
}

void CameraComponent::AddDrawable(Drawable * drawable)
{
    _renderQueue.push_back(drawable);
    std::sort(
            _renderQueue.begin(),
            _renderQueue.end(),
            [](Drawable * lhs, Drawable * rhs)
            {
                return lhs->GetRenderPriority() < rhs->GetRenderPriority();
            });
}

void CameraComponent::RemoveDrawable(Drawable * drawable)
{
    _renderQueue.erase(std::remove(_renderQueue.begin(), _renderQueue.end(), drawable), _renderQueue.end());
}

void CameraComponent::FetchDependencies(const Entity & entity)
{
    _followPhysics = (*_physicsSystem)[_follows];
    if(_default)
    {
        _drawableSystem->SetDefaultCamera(this);
    }
}

void CameraComponent::Serialize(Archive & arc)
{
    arc(_renderPriority, "renderPriority");  
    arc(_scale, "scale");  
    arc(_default, "default");  
    arc.entity(_follows, "follows");  
    arc.system(_physicsSystem, "physics");
    arc.system(_drawableSystem, "drawable");
}

/* getters and setters */
void CameraComponent::SetScale(float scale) 
{ 
    _view.zoom(1 / _scale);
    _scale = scale; 
    _view.zoom(_scale);
}

/* System */
CameraSystem::CameraSystem(
        std::string name,
        SystemManager & manager) :
    UnorderedSystem(name, manager, UpdateStep::Update)
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
        float scale)
{
    CameraComponent * comp = new CameraComponent(
            originalView,
            renderPriority,
            scale);
    AttachComponent(entity, comp);
    return comp;
}
