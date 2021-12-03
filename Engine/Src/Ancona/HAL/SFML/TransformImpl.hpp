#ifndef Ancona_HAL_SFML_TransformImpl_H_
#define Ancona_HAL_SFML_TransformImpl_H_

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
}

}

}

#endif
