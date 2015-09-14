#include <Ancona/Core2D/Systems/Drawable/ContainerDrawable.hpp>

REGISTER_POLYMORPHIC_SERIALIZER(ild::ContainerDrawable);

using namespace ild;

ContainerDrawable::ContainerDrawable(
        const int priority,
        int priorityOffset,
        sf::Vector2f positionOffset) :
    Drawable(
            priority,
            priorityOffset,
            positionOffset)
{
}

void ContainerDrawable::Draw(sf::RenderWindow &window, sf::Transform parentTransform, float delta)
{
    Drawable::Draw(window, parentTransform, delta);
    auto & newTransform = parentTransform.combine(_transform);
    for (auto & drawable : _drawables)
    {
        drawable->Draw(window, newTransform, delta);
    }
}

void ContainerDrawable::FetchDependencies(const Entity &entity)
{
    Drawable::FetchDependencies(entity);
    for (auto & drawable : _drawables)
    {
        drawable->FetchDependencies(entity);
    }
}

void ContainerDrawable::Serialize(Archive & arc)
{
    Drawable::Serialize(arc);
    arc(_drawables, "drawables");
}

sf::Vector2u ContainerDrawable::size()
{
    float minX = INFINITY, minY = INFINITY, maxX = -INFINITY, maxY = -INFINITY;
    for (auto & drawable : _drawables)
    {
        sf::Vector2u drawableSize = drawable->size();

        float curX = drawable->positionOffset().x;
        if (curX - (drawableSize.x / 2) < minX)
        {
            minX = curX - (drawableSize.x / 2);
        }
        if (curX + (drawableSize.x / 2) > maxX)
        {
            maxX = curX + (drawableSize.x / 2);
        }

        float curY = drawable->positionOffset().y;
        if (curY - (drawableSize.y / 2) < minY)
        {
            minY = curY - (drawableSize.y / 2);
        }
        if (curY + (drawableSize.y / 2) > maxY)
        {
            maxY = curY + (drawableSize.y / 2);
        }
    }
    return sf::Vector2u(maxX - minX, maxY - minY);
}

int ContainerDrawable::alpha()
{
    if (_drawables[0] != nullptr)
    {
        return _drawables[0]->alpha();
    }
    return 0;
}

void ContainerDrawable::alpha(int alpha)
{
    for (auto & drawable : _drawables)
    {
        drawable->alpha(alpha);
    }
}
