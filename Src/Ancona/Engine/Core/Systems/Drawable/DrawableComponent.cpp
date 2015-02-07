#include <Ancona/Engine/Core/Systems/Drawable/DrawableComponent.hpp>
#include <Ancona/Engine/Core/Systems/Drawable/DrawableSystem.hpp>

using namespace ild;

DrawableComponent::DrawableComponent(
        DrawableSystem & drawableSystem,
        const PositionComponent & positionComponent) :
    _drawableSystem(drawableSystem),
    _positionComponent(positionComponent)
{
}

std::shared_ptr<SpriteDrawable> DrawableComponent::AddSprite(
        const std::string key,
        const std::string textureKey,
        const RenderPriorityEnum priority,
        int priorityOffset,
        sf::Vector2f positionOffset)
{
    std::shared_ptr<SpriteDrawable> sprite(new SpriteDrawable(
            _positionComponent,
            textureKey,
            priority,
            priorityOffset,
            positionOffset));

    _drawables[key] = sprite;
    _drawableSystem.AddDrawable(sprite);
    return sprite;
}

std::shared_ptr<AnimatedDrawable> DrawableComponent::AddAnimation(
        const std::string key,
        const std::string textureKey,
        const RenderPriorityEnum priority,
        sf::Vector2f frameDimensions,
        int numFrames,
        float duration,
        int priorityOffset,
        sf::Vector2f positionOffset)
{
    std::shared_ptr<AnimatedDrawable> animation(new AnimatedDrawable(
            _positionComponent,
            textureKey,
            priority,
            frameDimensions,
            numFrames,
            duration,
            priorityOffset,
            positionOffset));
    _drawables[key] = animation;
    _drawableSystem.AddDrawable(animation);
    return animation;
}

std::shared_ptr<TextDrawable> DrawableComponent::AddText(
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
    std::shared_ptr<TextDrawable> textDrawable(new TextDrawable(
            _positionComponent,
            text,
            fontKey,
            color,
            characterSize,
            priority,
            priorityOffset,
            positionOffset,
            smooth));
    _drawables[key] = textDrawable;
    _drawableSystem.AddDrawable(textDrawable);
    return textDrawable;
}

std::shared_ptr<ShapeDrawable> DrawableComponent::AddShape(
        const std::string key,
        sf::Shape & shape,
        const RenderPriorityEnum priority,
        int priorityOffset,
        sf::Vector2f positionOffset)
{
    std::shared_ptr<ShapeDrawable> shapeDrawable(new ShapeDrawable(
            _positionComponent,
            shape,
            priority,
            priorityOffset,
            positionOffset));
    _drawables[key] = shapeDrawable;
    _drawableSystem.AddDrawable(shapeDrawable);
    return shapeDrawable;
}

void DrawableComponent::RemoveDrawable(const std::string key)
{
    _drawableSystem.RemoveDrawable(_drawables[key]);
}

/* getters and setters */
std::vector<std::shared_ptr<Drawable> > DrawableComponent::GetDrawables()
{
    std::vector<std::shared_ptr<Drawable> > toReturn;
    for(std::map<std::string, std::shared_ptr<Drawable> >::iterator it = _drawables.begin(); it != _drawables.end(); ++it)
    {
        toReturn.push_back(it->second);
    }
    return toReturn;
}
