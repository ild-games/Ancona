#pragma once

#include <SFML/Graphics.hpp>

#include <Ancona/Graphics/Transform.hpp>

namespace ildhal
{

namespace priv
{

namespace TransformImpl
{
ild::Transform TranslateSfmlToAncona(const sf::Transform & transform);
sf::Transform TranslateAnconaToSfml(const ild::Transform & transform);
} // namespace TransformImpl

} // namespace priv

} // namespace ildhal
