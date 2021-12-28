#include <cmath>

#include <Ancona/Core2D/Systems/Drawable/ContainerDrawable.hpp>
#include <Ancona/Util2D/VectorMath.hpp>

REGISTER_POLYMORPHIC_SERIALIZER(ild::ContainerDrawable);

namespace ild
{

ContainerDrawable::ContainerDrawable(
    const float priority,
    const std::string & key,
    float priorityOffset,
    Vector2f anchor) :
        Drawable(priority, key, priorityOffset, anchor)
{
}

Drawable * ContainerDrawable::Copy()
{
    auto drawable = new ContainerDrawable();
    Drawable::CopyProperties(drawable);

    for (auto & childDrawable : _drawables)
    {
        drawable->AddDrawable(childDrawable->Copy());
    }
    return drawable;
}

void ContainerDrawable::OnDraw(ildhal::RenderTarget & target, Transform drawableTransform, float delta)
{
    for (auto & drawable : _drawables)
    {
        drawable->Draw(target, drawableTransform, delta);
    }
}

void ContainerDrawable::PostDrawUpdate(float delta)
{
    for (auto & childDrawable : _drawables)
    {
        childDrawable->PostDrawUpdate(delta);
    }
}

void ContainerDrawable::FetchDependencies(const Entity & entity)
{
    Drawable::FetchDependencies(entity);
    for (auto & drawable : _drawables)
    {
        drawable->FetchDependencies(entity);
    }
    SortDrawables();
}

Drawable * ContainerDrawable::FindDrawable(const std::string & key)
{
    Drawable * toReturn = Drawable::FindDrawable(key);
    if (toReturn == nullptr)
    {
        for (auto & drawable : _drawables)
        {
            toReturn = drawable->FindDrawable(key);
            if (toReturn != nullptr)
            {
                break;
            }
        }
    }
    return toReturn;
}

void ContainerDrawable::SortDrawables()
{
    alg::sort(
        _drawables,
        [](const std::shared_ptr<Drawable> & lhs, const std::shared_ptr<Drawable> & rhs)
        {
            return lhs->renderPriority() < rhs->renderPriority();
        });
}

void ContainerDrawable::Serialize(Archive & arc)
{
    Drawable::Serialize(arc);
    arc(_drawables, "drawables");
}

void ContainerDrawable::AddDrawable(Drawable * drawable)
{
    _drawables.emplace_back(drawable);
}

void ContainerDrawable::RemoveDrawable(const std::string & key)
{
    _drawables.erase(alg::remove_if(
        _drawables,
        [key](const std::shared_ptr<Drawable> & drawable)
        {
            return key == drawable->key();
        }));
}

Vector2f ContainerDrawable::size()
{
    float minX = INFINITY, minY = INFINITY, maxX = -INFINITY, maxY = -INFINITY;
    for (auto & drawable : _drawables)
    {
        if (!drawable->inactive())
        {
            Vector2f drawableSize = drawable->size();

            float curX = -(drawableSize.x * drawable->anchor().x);
            if (curX < minX)
            {
                minX = curX;
            }
            if (curX + drawableSize.x > maxX)
            {
                maxX = curX + drawableSize.x;
            }

            float curY = -(drawableSize.y * drawable->anchor().y);
            if (curY < minY)
            {
                minY = curY;
            }
            if (curY + drawableSize.y > maxY)
            {
                maxY = curY + drawableSize.y;
            }
        }
    }
    Vector2f size(maxX - minX, maxY - minY);
    return VectorMath::ComponentMultiplication(size, Vector2f(std::abs(_scale.x), std::abs(_scale.y)));
}

int ContainerDrawable::alpha()
{
    if (_drawables.size() != 0u)
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

Vector2f ContainerDrawable::position(Vector2f entityPosition)
{
    float minX = INFINITY, minY = INFINITY;
    for (auto & drawable : _drawables)
    {
        Vector2f drawablePosition = drawable->position(entityPosition);

        if (drawablePosition.x < minX)
        {
            minX = drawablePosition.x;
        }

        if (drawablePosition.y < minY)
        {
            minY = drawablePosition.y;
        }
    }

    auto size = this->size();
    return Vector2f(minX, minY) - Vector2f(size.x * _anchor.x, size.y * _anchor.y);
}

} // namespace ild
