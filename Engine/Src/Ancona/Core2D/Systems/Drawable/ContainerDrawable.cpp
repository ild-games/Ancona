#include <Ancona/Core2D/Systems/Drawable/ContainerDrawable.hpp>
#include <Ancona/Util2D/VectorMath.hpp>

REGISTER_POLYMORPHIC_SERIALIZER(ild::ContainerDrawable);

using namespace ild;

ContainerDrawable::ContainerDrawable(
        const int priority,
        const std::string & key,
        int priorityOffset,
        sf::Vector2f anchor) :
    Drawable(
            priority,
            key,
            priorityOffset,
            anchor)
{
}

void ContainerDrawable::OnDraw(sf::RenderWindow &window, sf::Transform drawableTransform, float delta)
{
    for (auto & drawable : _drawables)
    {
        if (_anchor.x != 0.0f || _anchor.y != 0.0f) {
            auto size = this->size();
            drawableTransform.translate(-(size.x * _anchor.x), -(size.y * _anchor.y)); 
        }
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

Drawable * ContainerDrawable::FindDrawable(const std::string & key)
{
    Drawable * toReturn = Drawable::FindDrawable(key);
    if (toReturn == nullptr)
    {
        for (auto &drawable : _drawables)
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
            [](const std::unique_ptr<Drawable> & lhs, const std::unique_ptr<Drawable> & rhs)
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
    _drawables.erase(alg::remove_if(_drawables, [key](const std::unique_ptr<Drawable> & drawable) {
        return key == drawable->key();
    }));
}

sf::Vector2f ContainerDrawable::size()
{
    float minX = INFINITY, minY = INFINITY, maxX = -INFINITY, maxY = -INFINITY;
    for (auto & drawable : _drawables)
    {
        sf::Vector2f drawableSize = drawable->size();

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
    sf::Vector2f size(maxX - minX, maxY - minY);
    return VectorMath::ComponentMultiplication(size, _scale);
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

sf::Vector2f ContainerDrawable::actualPosition(sf::Vector2f entityPosition)
{
    float minX = INFINITY, minY = INFINITY;
    for (auto & drawable : _drawables) {
        sf::Vector2f drawablePosition = drawable->actualPosition(entityPosition);
        
        if (drawablePosition.x < minX) {
            minX = drawablePosition.x;     
        }
        
        if (drawablePosition.y < minY) {
            minY = drawablePosition.y;     
        }
    }
    
    auto size = this->size();
    return sf::Vector2f(minX, minY) - sf::Vector2f(size.x * _anchor.x, size.y * _anchor.y);
}