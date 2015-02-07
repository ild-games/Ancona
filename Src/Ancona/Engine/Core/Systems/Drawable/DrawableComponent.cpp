#include <Ancona/Engine/Core/Systems/Drawable/DrawableComponent.hpp>
#include <Ancona/Engine/Core/Systems/Drawable/DrawableSystem.hpp>

#include <iostream>

using namespace ild;

DrawableComponent::DrawableComponent(
        DrawableSystem & drawableSystem,
        const PositionComponent & positionComponent) :
    _drawableSystem(drawableSystem),
    _positionComponent(positionComponent)
{
}

SpriteDrawable * DrawableComponent::AddSprite(
        const std::string key,
        const std::string textureKey,
        const RenderPriorityEnum priority,
        int priorityOffset,
        sf::Vector2f positionOffset)
{
    SpriteDrawable * sprite = new SpriteDrawable(
            _positionComponent,
            textureKey,
            priority,
            priorityOffset,
            positionOffset);

    _drawables[key] = sprite;
    _drawableSystem.AddDrawable(sprite);
    return sprite;
}

AnimatedDrawable * DrawableComponent::AddAnimation(
        const std::string key,
        const std::string textureKey,
        const RenderPriorityEnum priority,
        sf::Vector2f frameDimensions,
        int numFrames,
        float duration,
        float xGap,
        float yGap,
        int priorityOffset,
        sf::Vector2f positionOffset)
{
    AnimatedDrawable * animation = new AnimatedDrawable(
            _positionComponent,
            textureKey,
            priority,
            frameDimensions,
            numFrames,
            duration,
            xGap,
            yGap,
            priorityOffset,
            positionOffset);
    _drawables[key] = animation;
    _drawableSystem.AddDrawable(animation);
    return animation;
}

TextDrawable * DrawableComponent::AddText(
        const std::string key,
        const std::string text,
        const std::string fontKey,
        const sf::Color color,
        const int characterSize,
        const RenderPriorityEnum priority,
        int priorityOffset,
        sf::Vector2f positionOffset,
        bool smooth)
{
    TextDrawable * textDrawable = new TextDrawable(
            _positionComponent,
            text,
            fontKey,
            color,
            characterSize,
            priority,
            priorityOffset,
            positionOffset,
            smooth);
    _drawables[key] = textDrawable;
    _drawableSystem.AddDrawable(textDrawable);
    return textDrawable;
}

ShapeDrawable * DrawableComponent::AddShape(
        const std::string key,
        sf::Shape & shape,
        const RenderPriorityEnum priority,
        int priorityOffset,
        sf::Vector2f positionOffset)
{
    ShapeDrawable * shapeDrawable = new ShapeDrawable(
            _positionComponent,
            shape,
            priority,
            priorityOffset,
            positionOffset);
    _drawables[key] = shapeDrawable;
    _drawableSystem.AddDrawable(shapeDrawable);
    return shapeDrawable;
}

void DrawableComponent::RemoveDrawable(const std::string key)
{
    _drawableSystem.RemoveDrawable(_drawables[key]);
}

/* getters and setters */
std::vector<Drawable *> DrawableComponent::GetDrawables()
{
    std::vector<Drawable *> toReturn;
    for(std::map<std::string, Drawable *>::iterator it = _drawables.begin(); it != _drawables.end(); ++it)
    {
        toReturn.push_back(it->second);
    }
    return toReturn;
}
