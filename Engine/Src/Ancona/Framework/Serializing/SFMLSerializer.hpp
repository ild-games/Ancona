#ifndef Ancona_Engine_Serializing_SFMLSerializer_H_
#define Ancona_Engine_Serializing_SFMLSerializer_H_

#include <SFML/System.hpp>

#include <Ancona/Framework/Serializing/Archive.hpp>
#include <Ancona/Framework/Serializing/Serializer.hpp>
#include <Ancona/Framework/Serializing/StdSerializer.hpp>
#include <Ancona/Framework/Resource/ResourceLibrary.hpp>
#include <Ancona/System/Log.hpp>

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

    static const rapidjson::Type SerializingType() 
    {
        return rapidjson::Type::kObjectType;
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

    static const rapidjson::Type SerializingType() 
    {
        return rapidjson::Type::kObjectType;
    }
};

template <>
struct Serializer<sf::Text>
{
    static void Serialize(sf::Text & property, Archive & arc)
    {
        std::string text;
        std::string fontKey;
        sf::Color color;
        int characterSize;
        bool smooth = true;

        if (!arc.loading())
        {
            text = property.getString();
            characterSize = property.getCharacterSize();
            color = property.getFillColor();
            smooth = property.getFont()->getTexture(characterSize).isSmooth();
        }

        arc(text, "text");
        arc(color, "color");
        arc(characterSize,"characterSize");
        arc(smooth, "smooth");

        if (arc.loading())
        {
            arc(fontKey, "fontKey");
            property.setString(text);
            property.setFont(*ResourceLibrary::Get<sf::Font>(fontKey));
            property.setFillColor(color);
            property.setCharacterSize(characterSize);
            if (!smooth)
            {
                const_cast<sf::Texture&>(property.getFont()->getTexture(characterSize)).setSmooth(false);
            }
        }
    }

    static const rapidjson::Type SerializingType() 
    {
        return rapidjson::Type::kObjectType;
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

    static const rapidjson::Type SerializingType() 
    {
        return rapidjson::Type::kObjectType;
    }
};

template <>
struct Serializer<sf::Shape>
{
    static void Serialize(sf::Shape & shape, Archive & arc)
    {
        ILD_Assert(false, "Cannot serialize sf::Shape");
    }

    static const rapidjson::Type SerializingType() 
    {
        return rapidjson::Type::kObjectType;
    }
};

template <>
struct Serializer<sf::RectangleShape>
{
    static void Serialize(sf::RectangleShape & shape, Archive & arc);

    static const rapidjson::Type SerializingType() 
    {
        return rapidjson::Type::kObjectType;
    }
};

template <>
struct Serializer<sf::CircleShape>
{
    static void Serialize(sf::CircleShape & shape, Archive & arc);

    static const rapidjson::Type SerializingType() 
    {
        return rapidjson::Type::kObjectType;
    }
};

template <>
struct Serializer<sf::IntRect>
{
    static void Serialize(sf::IntRect & rect, Archive & arc)
    {
        arc(rect.left, "left");
        arc(rect.top, "top");
        arc(rect.width, "width");
        arc(rect.height, "height");
    }

    static const rapidjson::Type SerializingType() 
    {
        return rapidjson::Type::kObjectType;
    }
};

}

GENERATE_ABSTRACT_CLASS_CONSTRUCTOR(sf::Shape)

#endif
