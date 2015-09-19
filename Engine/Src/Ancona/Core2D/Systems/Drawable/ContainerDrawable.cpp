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

void ContainerDrawable::OnDraw(sf::RenderWindow &window, sf::Transform drawableTransform, float delta)
{
    for (auto & drawable : _drawables)
    {
        drawable->Draw(window, drawableTransform, delta);
    }
}

void ContainerDrawable::FetchDependencies(const Entity &entity)
{
    Drawable::FetchDependencies(entity);
    for (auto & drawable : _drawables)
    {
        drawable->FetchDependencies(entity);
    }
    SortDrawables();
}

void ContainerDrawable::SortDrawables()
{
    alg::sort(
            _drawables,
            [](Drawable * lhs, Drawable * rhs)
            {
                return lhs->renderPriority() < rhs->renderPriority();
            });
}

void ContainerDrawable::Serialize(Archive & arc)
{
    Drawable::Serialize(arc);
    arc(_drawables, "drawables");
}

sf::Vector2f ContainerDrawable::size()
{
    float minX = INFINITY, minY = INFINITY, maxX = -INFINITY, maxY = -INFINITY;
    for (auto & drawable : _drawables)
    {
        sf::Vector2f drawableSize = drawable->size();

        float curX = drawable->positionOffset().x;
        if (curX - (drawableSize.x / 2.0f) < minX)
        {
            minX = curX - (drawableSize.x / 2.0f);
        }
        if (curX + (drawableSize.x / 2.0f) > maxX)
        {
            maxX = curX + (drawableSize.x / 2.0f);
        }

        float curY = drawable->positionOffset().y;
        if (curY - (drawableSize.y / 2.0f) < minY)
        {
            minY = curY - (drawableSize.y / 2.0f);
        }
        if (curY + (drawableSize.y / 2.0f) > maxY)
        {
            maxY = curY + (drawableSize.y / 2.0f);
        }
    }
    return sf::Vector2f(maxX - minX, maxY - minY);
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
