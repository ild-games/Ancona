#include <Ancona/Engine/Core/Systems/Drawable/DrawableSystem.hpp>
#include <Ancona/Engine/EntityFramework/UpdateStep.hpp>

using namespace ild;


DrawableSystem::DrawableSystem(
        sf::RenderWindow & window, 
        SystemManager & systemManager, 
        PositionSystem & positionSystem) : 
    UnorderedSystem(systemManager, UpdateStep::Draw), 
    _window(window), 
    _positionSystem(positionSystem)
{
}

void DrawableSystem::Update(float delta)
{
    for(std::shared_ptr<Drawable> drawable : _renderQueue)
    {
        drawable->Draw(_window, delta);
    }
}

void DrawableSystem::AddDrawable(std::shared_ptr<Drawable> drawable)
{
    _renderQueue.push_back(drawable);
    std::sort(
            _renderQueue.begin(), 
            _renderQueue.end(), 
            [](std::shared_ptr<Drawable> lhs, std::shared_ptr<Drawable> rhs)
            {
                return (lhs->GetRenderPriority()) <
                       (rhs->GetRenderPriority());
            });
}

void DrawableSystem::RemoveDrawable(std::shared_ptr<Drawable> drawable)
{
    _renderQueue.erase(std::remove(_renderQueue.begin(), _renderQueue.end(), drawable), _renderQueue.end());
}

DrawableComponent * DrawableSystem::CreateComponent(const Entity & entity)
{
    auto comp = new DrawableComponent(
            *this,
            *_positionSystem[entity]);
    AttachComponent(entity, comp);
    return comp;
}

void DrawableSystem::OnComponentRemove(Entity entity, DrawableComponent * component)
{
    std::vector<std::shared_ptr<Drawable> > compDrawables = component->GetDrawables();
    for(std::shared_ptr<Drawable> drawable : compDrawables)
    {
        _renderQueue.erase(std::remove(_renderQueue.begin(), _renderQueue.end(), drawable), _renderQueue.end());
    }
}

