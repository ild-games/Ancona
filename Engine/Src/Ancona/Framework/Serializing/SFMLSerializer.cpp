#include <SFML/Graphics/RectangleShape.hpp>

#include <Ancona/Framework/Serializing/Serializing.hpp>

REGISTER_POLYMORPHIC_SERIALIZER_ABSTRACT_BASE(sf::Shape);
REGISTER_POLYMORPHIC_SERIALIZER(sf::RectangleShape);

using namespace ild;

void Serializer<sf::RectangleShape>::Serialize(sf::RectangleShape & shape, Archive & arc){
    sf::Vector2f dim;
    sf::Color color;
    if (!arc.loading()) {
        dim = shape.getSize();
        color = shape.getFillColor();
    }
    arc(dim, "dimension");
    arc(color, "fillColor");

    if (arc.loading())
    {
        shape.setSize(dim);
        shape.setFillColor(color);
    }
}

void Serializer<sf::OvalShape>::Serialize(sf::OvalShape & shape, Archive & arc){
    float radiusWidth;
    float radiusHeight;
    sf::Color color;
    if (!arc.loading()) {
        radiusWidth = shape.getRadiusWidth();
        radiusHeight = shape.getRadiusHeight();
        color = shape.getFillColor();
    }
    arc(radiusWidth, "radiusWidth");
    arc(radiusHeight, "radiusHeight");
    arc(color, "fillColor");

    if (arc.loading())
    {
        shape.setRadiusWidth(radiusWidth);
        shape.setRadiusHeight(radiusHeight);
        shape.setFillColor(color);
    }
}
