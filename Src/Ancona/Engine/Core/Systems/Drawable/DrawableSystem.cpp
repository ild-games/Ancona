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


void DrawableSystem::AttachComponent(
        const Entity & entity,
        DrawableComponent & component,
        const RenderPriorityEnum priority,
        int priorityOffset)
{
    UnorderedSystem::AttachComponent(entity, &component);
    _renderQueue.push_back(&component);
    std::sort(
            _renderQueue.begin(), 
            _renderQueue.end(), 
            [](DrawableComponent * lhs, DrawableComponent * rhs)
            {
                return (lhs->GetRenderPriority() + lhs->GetPriorityOffset()) <
                       (rhs->GetRenderPriority() + rhs->GetPriorityOffset());
            });

}


SpriteComponent * DrawableSystem::CreateSpriteComponent(
        const Entity & entity, 
        const std::string & textureKey,
        const RenderPriorityEnum priority,
        int priorityOffset)
{
    auto positionComponent = _positionSystem[entity];

    Assert(
            positionComponent != nullptr,
            "A sprite component can only be attached to an entity with a position component");

    SpriteComponent * component = new SpriteComponent(
            *positionComponent,
            textureKey,
            priority,
            priorityOffset);
    AttachComponent(
            entity, 
            *component,
            priority,
            priorityOffset);

    return component;
}

TextComponent * DrawableSystem::CreateTextComponent(
        const Entity & entity,
        const std::string text,
        const std::string fontKey,
        const sf::Color color,
        const int characterSize,
        const RenderPriorityEnum priority,
        int priorityOffset,
        bool smooth)
{
    auto positionComponent = _positionSystem[entity];

    Assert(
            positionComponent != nullptr,
            "A text component can only be attached to an entity with a position component");

    TextComponent * component = new TextComponent(
            *positionComponent,
            text,
            fontKey,
            color,
            characterSize,
            priority,
            priorityOffset,
            smooth);
    AttachComponent(
            entity, 
            *component,
            priority,
            priorityOffset);

    return component;
}

void DrawableSystem::OnComponentRemove(Entity entity, DrawableComponent * component)
{
    _renderQueue.erase(std::remove(_renderQueue.begin(), _renderQueue.end(), component), _renderQueue.end());
}

void DrawableSystem::Update(float delta)
{
    for(DrawableComponent * drawableComp : _renderQueue)
    {
        drawableComp->Draw(_window);
    }
}

