#include <Ancona/HAL/SFML/DrawableImpl.hpp>
#include <Ancona/HAL/SFML/RenderTargetImpl.hpp>
#include <Ancona/HAL/SFML/RenderStatesImpl.hpp>
#include <Ancona/HAL/SFML/ViewImpl.hpp>

namespace ildhal
{

/* HAL Interface Implementation */

void RenderTarget::Clear(const ild::Color & color)
{
    auto sfmlColor = sf::Color(color.toInteger());
    renderTargetImpl().sfmlRenderTarget().clear(sfmlColor);
}

void RenderTarget::Draw(const Drawable & drawable, const RenderStates & states)
{
    renderTargetImpl().sfmlRenderTarget().draw(
        drawable.drawableImpl().sfmlDrawable(),
        states.renderStatesImpl().sfmlRenderStates());
}

ild::Vector2f RenderTarget::MapPixelToCoords(const ild::Vector2i & point, const ild::View & view) const
{
    auto sfmlPoint = sf::Vector2i(point.x, point.y);
    sf::View sfmlView;
    priv::ViewImpl::TranslateAnconaToSfml(view, sfmlView);
    auto coords = renderTargetImpl().sfmlRenderTarget().mapPixelToCoords(sfmlPoint, sfmlView);
    return ild::Vector2f(coords.x, coords.y);
}

void RenderTarget::ResetGLStates()
{
    renderTargetImpl().sfmlRenderTarget().resetGLStates();
}

/* getters and setters */
const ild::View & RenderTarget::defaultView() const
{
    auto sfmlView = renderTargetImpl().sfmlRenderTarget().getDefaultView();
    ild::View view;
    priv::ViewImpl::TranslateSfmlToAncona(sfmlView, view);
    return view;
}

void RenderTarget::view(const ild::View & view)
{
    sf::View sfmlView = renderTargetImpl().sfmlRenderTarget().getView();
    priv::ViewImpl::TranslateAnconaToSfml(view, sfmlView);
    renderTargetImpl().sfmlRenderTarget().setView(sfmlView);
}

}
