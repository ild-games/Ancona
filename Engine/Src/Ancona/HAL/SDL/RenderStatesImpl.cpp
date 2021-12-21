#include <SFML/Graphics.hpp>

#include <Ancona/HAL/SDL/BlendModeImpl.hpp>
#include <Ancona/HAL/SDL/RenderStatesImpl.hpp>
#include <Ancona/HAL/SDL/TextureImpl.hpp>
#include <Ancona/HAL/SDL/TransformImpl.hpp>

namespace ildhal
{

/* Pimpl Implementation */

priv::RenderStatesImpl::RenderStatesImpl(
    const sf::BlendMode & blendMode,
    const sf::Transform & transform,
    const sf::Texture * texture)
{
    _sfmlRenderStates = std::make_unique<sf::RenderStates>(blendMode, transform, texture, nullptr);
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
    _pimpl = std::make_unique<priv::RenderStatesImpl>(sf::BlendAlpha, sf::Transform(), nullptr);
}

RenderStates::RenderStates(const BlendMode & blendMode)
{
    sf::BlendMode sfmlBlendMode;
    priv::BlendModeImpl::TranslateAnconaToSfml(blendMode, sfmlBlendMode);

    _pimpl = std::make_unique<priv::RenderStatesImpl>(sfmlBlendMode, sf::Transform(), nullptr);
}

RenderStates::RenderStates(const ild::Transform & transform)
{
    auto sfmlTransform = priv::TransformImpl::TranslateAnconaToSfml(transform);

    _pimpl = std::make_unique<priv::RenderStatesImpl>(sf::BlendAlpha, sfmlTransform, nullptr);
}

RenderStates::RenderStates(const BlendMode & blendMode, const ild::Transform & transform, const Texture & texture)
{
    sf::BlendMode sfmlBlendMode;
    priv::BlendModeImpl::TranslateAnconaToSfml(blendMode, sfmlBlendMode);

    auto sfmlTransform = priv::TransformImpl::TranslateAnconaToSfml(transform);

    auto sfmlTexture = nullptr;

    _pimpl = std::make_unique<priv::RenderStatesImpl>(sfmlBlendMode, sfmlTransform, sfmlTexture);
}

} // namespace ildhal
