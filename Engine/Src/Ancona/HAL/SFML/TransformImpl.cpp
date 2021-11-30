#include <Ancona/HAL/SFML/TransformImpl.hpp>

namespace ildhal
{

ild::Transform priv::TransformImpl::TranslateSfmlToAncona(const sf::Transform & transform)
{
    auto matrix = transform.getMatrix();
    ild::Transform ildTransform(
        matrix[0], matrix[4], matrix[12],
        matrix[1], matrix[5], matrix[13],
        matrix[3], matrix[7], matrix[15]);

    return ildTransform;
}

sf::Transform priv::TransformImpl::TranslateAnconaToSfml(const ild::Transform & transform)
{
    auto matrix = transform.matrix();
    sf::Transform sfmlTransform(
        matrix[0], matrix[4], matrix[12],
        matrix[1], matrix[5], matrix[13],
        matrix[3], matrix[7], matrix[15]);

    return sfmlTransform;
}

}
