#include <Ancona/Framework/Serializing/Serializing.hpp>
#include <Ancona/Util/Vector2.hpp>

REGISTER_POLYMORPHIC_SERIALIZER_ABSTRACT_BASE(ildhal::Shape);
REGISTER_POLYMORPHIC_SERIALIZER(ildhal::RectangleShape);
REGISTER_POLYMORPHIC_SERIALIZER(ildhal::CircleShape);

using namespace ild;

void Serializer<ildhal::RectangleShape>::Serialize(ildhal::RectangleShape & shape, Archive & arc)
{
    Vector2f dim;
    Color color;
    if (!arc.loading())
    {
        dim = shape.size();
        color = shape.fillColor();
    }
    arc(dim, "dimension");
    arc(color, "fillColor");

    if (arc.loading())
    {
        shape.size(dim);
        shape.fillColor(color);
    }
}

void Serializer<ildhal::CircleShape>::Serialize(ildhal::CircleShape & shape, Archive & arc)
{
    float radius;
    Color color;
    if (!arc.loading())
    {
        radius = shape.radius();
        color = shape.fillColor();
    }
    arc(radius, "radius");
    arc(color, "fillColor");

    if (arc.loading())
    {
        shape.radius(radius);
        shape.fillColor(color);
    }
}
