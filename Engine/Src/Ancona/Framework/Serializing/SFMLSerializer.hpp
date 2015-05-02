#ifndef Ancona_Engine_Serializing_SFMLSerializer_H_
#define Ancona_Engine_Serializing_SFMLSerializer_H_

#include <SFML/System.hpp>

#include <Ancona/Framework/Serializing/Archive.hpp>
#include <Ancona/Framework/Serializing/Serializer.hpp>
#include <Ancona/Framework/Serializing/StdSerializer.hpp>
#include <Ancona/Framework/Resource/ResourceLibrary.hpp>

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

template <>
struct Serializer<sf::Text>
{
    static void Serialize(sf::Text & property, Archive & arc)
    {
        if (arc.loading())
        {
            std::string text;
            std::string fontKey;
            sf::Color color;
            int characterSize;
            bool smooth;
            arc(text, "text");
            arc(fontKey, "font-key");
            arc(color, "color");
            arc(characterSize,"character-size");
            arc(smooth, "smooth");

            property.setString(text);
            property.setFont(*ResourceLibrary::Get<sf::Font>(fontKey));
            property.setColor(color);
            if (!smooth)
            {
                const_cast<sf::Texture&>(property.getFont()->getTexture(characterSize)).setSmooth(false);
            }
        }
        else
        {

            //TODO ANC-80 Implement saving
        }
    }
};

template <>
struct Serializer<sf::Color>
{
    static void Serialize(sf::Color & property, Archive & arc)
    {
        arc(property.r,"r");
        arc(property.g,"g");
        arc(property.b,"b");
        arc(property.a,"a");
    }
};

template <>
struct Serializer<sf::Shape>
{
    static void Serialize(sf::Shape & shape, Archive & arc)
    {
        Assert(false, "Cannot serialize sf::Shape");
    }
};

template <>
struct Serializer<sf::RectangleShape>
{
    static void Serialize(sf::RectangleShape & shape, Archive & arc);
};

}

GENERATE_ABSTRACT_CLASS_CONSTRUCTOR(sf::Shape)

#endif
