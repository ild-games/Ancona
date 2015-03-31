//
// Created by jeff on 3/29/15.
//

#include <SFML/Graphics/RectangleShape.hpp>
#include <Ancona/Engine/Loading/Loading.hpp>

REGISTER_POLYMORPHIC_SERIALIZER_ABSTRACT_BASE(sf::Shape);
REGISTER_POLYMORPHIC_SERIALIZER(sf::RectangleShape);

using namespace ild;

void Serializer<sf::RectangleShape>::Serialize(sf::RectangleShape & shape, Archive & arc){
    sf::Vector2f dim;
    if (!arc.IsLoading()) {
        dim = shape.getSize();
    }
    arc(dim.x, "width");
    arc(dim.y, "height");
    if (arc.IsLoading())
    {
        shape.setSize(dim);
    }
}