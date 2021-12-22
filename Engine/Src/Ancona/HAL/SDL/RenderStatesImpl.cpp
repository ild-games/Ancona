#include <Ancona/HAL/SDL/RenderStatesImpl.hpp>

namespace ildhal
{

/* Pimpl Implementation */

priv::RenderStatesImpl::RenderStatesImpl(const ildhal::BlendMode & blendMode, const ild::Transform & transform) :
        _blendMode(blendMode),
        _transform(transform)
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
    _pimpl = std::make_unique<priv::RenderStatesImpl>(BlendAlpha, ild::Transform());
}

RenderStates::RenderStates(const BlendMode & blendMode)
{
    _pimpl = std::make_unique<priv::RenderStatesImpl>(blendMode, ild::Transform());
}

RenderStates::RenderStates(const ild::Transform & transform)
{
    _pimpl = std::make_unique<priv::RenderStatesImpl>(BlendAlpha, transform);
}

RenderStates::RenderStates(const BlendMode & blendMode, const ild::Transform & transform, const Texture & texture)
{
    _pimpl = std::make_unique<priv::RenderStatesImpl>(blendMode, transform);
}

} // namespace ildhal
