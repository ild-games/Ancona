#ifndef Ancona_HAL_SFML_BlendModeImpl_H_
#define Ancona_HAL_SFML_BlendModeImpl_H_

#include <SFML/Graphics.hpp>

#include <Ancona/HAL/BlendMode.hpp>

namespace ildhal
{

namespace priv
{

namespace BlendModeImpl
{
void TranslateSfmlToAncona(const sf::BlendMode &sfmlBlendMode, BlendMode &blendMode);
void TranslateAnconaToSfml(const BlendMode &blendMode, sf::BlendMode &sfmlBlendMode);
} // namespace BlendModeImpl

} // namespace priv

} // namespace ildhal

#endif
