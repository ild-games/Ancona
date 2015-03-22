#ifndef Ancona_Engine_Loading_SFMLSerializer_H_
#define Ancona_Engine_Loading_SFMLSerializer_H_

#include <SFML/System.hpp>

#include <Ancona/Engine/Loading/Archive.hpp>
#include <Ancona/Engine/Loading/Serializer.hpp>

namespace ild
{

template <class sf::Vector2f>
struct Serializer
{
    static void Serialize(sf::Vector2f & property, Archive & arc)
    {
        arc(property.x, "x");
        arc(property.y, "y");
    }
};

template <class sf::Vector3f>
struct Serializer
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
