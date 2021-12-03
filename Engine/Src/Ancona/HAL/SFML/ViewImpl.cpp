#include <Ancona/HAL/SFML/ViewImpl.hpp>

namespace ildhal
{

void priv::ViewImpl::TranslateSfmlToAncona(const sf::View &sfmlView, ild::View &view)
{
    auto sfmlCenter = sfmlView.getCenter();
    view.center(sfmlCenter.x, sfmlCenter.y);

    auto sfmlSize = sfmlView.getSize();
    view.size(sfmlSize.x, sfmlSize.y);

    auto sfmlRotation = sfmlView.getRotation();
    view.rotation(sfmlRotation);

    auto sfmlViewport = sfmlView.getViewport();
    view.viewport(ild::FloatRect(sfmlViewport.left, sfmlViewport.top, sfmlViewport.width, sfmlViewport.height));
}

void priv::ViewImpl::TranslateAnconaToSfml(const ild::View &view, sf::View &sfmlView)
{
    auto center = view.center();
    sfmlView.setCenter(center.x, center.y);

    auto size = view.size();
    sfmlView.setSize(size.x, size.y);

    auto rotation = view.rotation();
    sfmlView.setRotation(rotation);

    auto viewport = view.viewport();
    sfmlView.setViewport(sf::FloatRect(viewport.left, viewport.top, viewport.width, viewport.height));
}

} // namespace ildhal
