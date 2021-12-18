#include <memory>

#include <Ancona/HAL/SDL/RectangleShapeImpl.hpp>

namespace ildhal
{

/* Pimpl Implementation */

priv::RectangleShapeImpl::RectangleShapeImpl()
{
    _sfmlDrawable = std::make_unique<sf::RectangleShape>();
}

priv::RectangleShapeImpl::RectangleShapeImpl(const sf::Vector2f & size)
{
    _sfmlDrawable = std::make_unique<sf::RectangleShape>(size);
}

sf::RectangleShape & priv::RectangleShapeImpl::sfmlRectangleShape() const
{
    return static_cast<sf::RectangleShape &>(*_sfmlDrawable);
}

/* HAL Interface Implementation */

RectangleShape::RectangleShape()
{
    _pimpl = std::make_unique<priv::RectangleShapeImpl>();
}

RectangleShape::RectangleShape(const ild::Vector2f & size)
{
    _pimpl = std::make_unique<priv::RectangleShapeImpl>(sf::Vector2f(size.x, size.y));
}

/* getters and setters */

const ild::Vector2f RectangleShape::size() const
{
    auto sfmlSize = rectangleShapeImpl().sfmlRectangleShape().getSize();
    return ild::Vector2f(sfmlSize.x, sfmlSize.y);
}

void RectangleShape::size(const ild::Vector2f & newSize)
{
    rectangleShapeImpl().sfmlRectangleShape().setSize(sf::Vector2f(newSize.x, newSize.y));
}

priv::RectangleShapeImpl & RectangleShape::rectangleShapeImpl() const
{
    return static_cast<priv::RectangleShapeImpl &>(*_pimpl);
}

} // namespace ildhal
