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
    RenderStatesImpl(const ildhal::BlendMode & blendMode, const ild::Transform & transform);

    /* getters and setters */
    const ildhal::BlendMode & blendMode() const { return _blendMode; }
    const ild::Transform & transform() const { return _transform; }

  protected:
    ildhal::BlendMode _blendMode;
    ild::Transform _transform;
};

} // namespace priv

} // namespace ildhal
