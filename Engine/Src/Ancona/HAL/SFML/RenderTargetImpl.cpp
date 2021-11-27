#include <Ancona/HAL/SFML/RenderTargetImpl.hpp>

using namespace ildhal;

/* Pimpl Implementation */

priv::RenderTargetImpl::RenderTargetImpl(
    std::unique_ptr<sf::RenderTarget> sfmlRenderTarget) :
        _sfmlRenderTarget(std::move(sfmlRenderTarget))
{
}

/* HAL Interface Implementation */

void RenderTarget::Clear(const Color & color)
{
    _pimpl->getSfmlRenderTarget().clear(sf::Color(color.toInteger()));
}

void RenderTarget::Draw(const sf::Drawable & drawable, const sf::RenderStates & states)
{
    _pimpl->getSfmlRenderTarget().draw(drawable, states);
}

void RenderTarget::SetView(const sf::View & view)
{
    _pimpl->getSfmlRenderTarget().setView(view);
}

const sf::View & RenderTarget::GetDefaultView() const
{
    return _pimpl->getSfmlRenderTarget().getDefaultView();
}

ild::Vector2f RenderTarget::MapPixelToCoords(const ild::Vector2i & point, const sf::View & view) const
{
    auto sfmlPoint = sf::Vector2i(point.x, point.y);
    auto coords = _pimpl->getSfmlRenderTarget().mapPixelToCoords(sfmlPoint, view);
    return ild::Vector2f(coords.x, coords.y);
}

void RenderTarget::ResetGLStates()
{
    _pimpl->getSfmlRenderTarget().resetGLStates();
}
