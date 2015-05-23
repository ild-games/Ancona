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
    arc(dim.x, "width");
    arc(dim.y, "height");
    arc(color, "fill-color");

    if (arc.loading())
    {
        shape.setSize(dim);
        shape.setFillColor(color);
    }
}
