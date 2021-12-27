#pragma once

#include <Ancona/Graphics/Transform.hpp>
#include <Ancona/HAL/RenderStates.hpp>

namespace ildhal
{

namespace priv
{

class RenderStatesImpl
{
  public:
    RenderStatesImpl(
        const ildhal::BlendMode & blendMode,
        const ild::Transform & transform,
        const ildhal::Texture & texture);

    /* getters and setters */
    const ildhal::BlendMode & blendMode() const { return _blendMode; }
    void blendMode(const ildhal::BlendMode & newBlendMode) { _blendMode = newBlendMode; }
    const ild::Transform & transform() const { return _transform; }
    void transform(const ild::Transform & newTransform) { _transform = newTransform; }
    const ildhal::Texture & texture() const { return _texture; }
    const ild::Vector2f & size() const { return _size; }
    void size(const ild::Vector2f & newSize) { _size = newSize; }

  protected:
    ildhal::BlendMode _blendMode;
    ild::Transform _transform;
    const ildhal::Texture & _texture;
    ild::Vector2f _size;
};

} // namespace priv

} // namespace ildhal
