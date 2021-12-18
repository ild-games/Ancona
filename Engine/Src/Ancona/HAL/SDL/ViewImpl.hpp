#ifndef Ancona_HAL_SFML_ViewImpl_H_
#define Ancona_HAL_SFML_ViewImpl_H_

#include <SFML/Graphics.hpp>

#include <Ancona/Graphics/View.hpp>

namespace ildhal
{

namespace priv
{

namespace ViewImpl
{
void TranslateSfmlToAncona(const sf::View &sfmlView, ild::View &view);
void TranslateAnconaToSfml(const ild::View &view, sf::View &sfmlView);
} // namespace ViewImpl

} // namespace priv

} // namespace ildhal

#endif
