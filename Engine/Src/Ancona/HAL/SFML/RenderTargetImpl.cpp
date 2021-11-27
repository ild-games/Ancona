#include <Ancona/HAL/SFML/RenderTargetImpl.hpp>

using namespace ildhal;

/* Pimpl Implementation */

priv::RenderTargetImpl::RenderTargetImpl(
    std::unique_ptr<sf::RenderTarget> sfmlRenderTarget) :
        _sfmlRenderTarget(std::move(sfmlRenderTarget))
{
}

/* HAL Interface Implementation */

void RenderTarget::Clear(const sf::Color & color)
{
    _pimpl->getSfmlRenderTarget().clear(color);
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

sf::Vector2f RenderTarget::MapPixelToCoords(const sf::Vector2i & point, const sf::View & view) const
{
    return _pimpl->getSfmlRenderTarget().mapPixelToCoords(point, view);
}

void RenderTarget::ResetGLStates()
{
    _pimpl->getSfmlRenderTarget().resetGLStates();
}
