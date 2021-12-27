#pragma once

#include <Ancona/Graphics/Color.hpp>
#include <Ancona/HAL/SDL/DrawableImpl.hpp>
#include <Ancona/HAL/Shape.hpp>
#include <Ancona/Util/Vector2.hpp>

namespace ildhal
{

namespace priv
{

class ShapeImpl : public DrawableImpl
{
  public:
    /* getters and setters */
    const ild::Vector2f & origin() const { return _origin; }
    void origin(const ild::Vector2f & newOrigin) { _origin = newOrigin; }
    const ild::Color & fillColor() const { return _fillColor; }
    void fillColor(const ild::Color & newFillColor) { _fillColor = newFillColor; }
    const ild::Color & outlineColor() const { return _outlineColor; }
    void outlineColor(const ild::Color & newOutlineColor) { _outlineColor = newOutlineColor; }

  protected:
    ild::Vector2f _origin;
    ild::Color _fillColor;
    ild::Color _outlineColor;
};

} // namespace priv

} // namespace ildhal
