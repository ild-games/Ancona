#ifndef Ancona_Engine_Loading_SFMLSerializer_H_
#define Ancona_Engine_Loading_SFMLSerializer_H_

#include <SFML/System.hpp>

#include <Ancona/Engine/Loading/Archive.hpp>
#include <Ancona/Engine/Loading/Serializer.hpp>

namespace ild
{

template <>
struct Serializer<sf::Vector2f>
{
    static void Serialize(sf::Vector2f & property, Archive & arc)
    {
        arc(property.x, "x");
        arc(property.y, "y");
    }
};

template <>
struct Serializer<sf::Vector3f>
{
    static void Serialize(sf::Vector3f & property, Archive & arc)
    {
        arc(property.x, "x");
        arc(property.y, "y");
        arc(property.z, "z");
    }
};

}

#endif
