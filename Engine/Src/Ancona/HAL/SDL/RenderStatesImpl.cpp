#include <Ancona/HAL/SDL/RenderStatesImpl.hpp>
#include <Ancona/HAL/SDL/TextureImpl.hpp>

namespace ildhal
{

/* Pimpl Implementation */

priv::RenderStatesImpl::RenderStatesImpl(
    const ildhal::BlendMode & blendMode,
    const ild::Transform & transform,
    const ildhal::Texture & texture) :
        _blendMode(blendMode),
        _transform(transform),
        _texture(texture)
{
}

/* HAL Interface Implementation */

const RenderStates RenderStates::Default(BlendMode(
    BlendMode::SrcAlpha,
    BlendMode::OneMinusSrcAlpha,
    BlendMode::Add,
    BlendMode::One,
    BlendMode::OneMinusSrcAlpha,
    BlendMode::Add));

RenderStates::RenderStates()
{
    _pimpl = std::make_unique<priv::RenderStatesImpl>(BlendAlpha, ild::Transform(), ildhal::Texture());
}

RenderStates::RenderStates(const BlendMode & blendMode)
{
    _pimpl = std::make_unique<priv::RenderStatesImpl>(blendMode, ild::Transform(), ildhal::Texture());
}

RenderStates::RenderStates(const ild::Transform & transform)
{
    _pimpl = std::make_unique<priv::RenderStatesImpl>(BlendAlpha, transform, ildhal::Texture());
}

RenderStates::RenderStates(const BlendMode & blendMode, const ild::Transform & transform, const Texture & texture)
{
    _pimpl = std::make_unique<priv::RenderStatesImpl>(blendMode, transform, texture);
}

/* getters and setters */
void RenderStates::blendMode(const ildhal::BlendMode & newBlendMode)
{
    renderStatesImpl().blendMode(newBlendMode);
}

void RenderStates::transform(const ild::Transform & newTransform)
{
    renderStatesImpl().transform(newTransform);
}

void RenderStates::size(const ild::Vector2f & newSize)
{
    renderStatesImpl().size(newSize);
}

} // namespace ildhal
