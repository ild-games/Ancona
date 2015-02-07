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
    for(Drawable * drawable : _renderQueue)
    {
        drawable->Draw(_window, delta);
    }
}

void DrawableSystem::AddDrawable(Drawable * drawable)
{
    _renderQueue.push_back(drawable);
    std::sort(
            _renderQueue.begin(), 
            _renderQueue.end(), 
            [](Drawable * lhs, Drawable * rhs)
            {
                return (lhs->GetRenderPriority()) <
                       (rhs->GetRenderPriority());
            });
}

void DrawableSystem::RemoveDrawable(Drawable * drawable)
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
    std::vector<Drawable *> compDrawables = component->GetDrawables();
    for(Drawable * drawable : compDrawables)
    {
        _renderQueue.erase(std::remove(_renderQueue.begin(), _renderQueue.end(), drawable), _renderQueue.end());
    }
}

