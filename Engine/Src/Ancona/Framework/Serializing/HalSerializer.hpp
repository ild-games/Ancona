#ifndef Ancona_Engine_Serializing_HalSerializer_H_
#define Ancona_Engine_Serializing_HalSerializer_H_

#include <Ancona/Framework/Serializing/Archive.hpp>
#include <Ancona/Framework/Serializing/Serializer.hpp>
#include <Ancona/Framework/Serializing/StdSerializer.hpp>
#include <Ancona/Framework/Resource/ResourceLibrary.hpp>
#include <Ancona/Graphics/Color.hpp>
#include <Ancona/Graphics/Rect.hpp>
#include <Ancona/HAL.hpp>
#include <Ancona/System/Log.hpp>

namespace ild
{

template <>
struct Serializer<ildhal::Text>
{
    static void Serialize(ildhal::Text & property, Archive & arc)
    {
        std::string text;
        std::string fontKey;
        Color color;
        int characterSize;
        bool smooth = true;

        if (!arc.loading())
        {
            text = property.string();
            characterSize = property.characterSize();
            color = property.fillColor();
            smooth = property.smooth();
        }

        arc(text, "text");
        arc(color, "color");
        arc(characterSize,"characterSize");
        arc(smooth, "smooth");

        if (arc.loading())
        {
            arc(fontKey, "fontKey");
            property.string(text);
            property.fontKey(fontKey);
            property.fillColor(color);
            property.characterSize(characterSize);
            if (!smooth)
            {
                property.smooth(false);
            }
        }
    }

    static const rapidjson::Type SerializingType() 
    {
        return rapidjson::Type::kObjectType;
    }
};

template <>
struct Serializer<ildhal::Shape>
{
    static void Serialize(ildhal::Shape & shape, Archive & arc)
    {
        ILD_Assert(false, "Cannot serialize ildhal::Shape");
    }

    static const rapidjson::Type SerializingType() 
    {
        return rapidjson::Type::kObjectType;
    }
};

template <>
struct Serializer<ildhal::RectangleShape>
{
    static void Serialize(ildhal::RectangleShape & shape, Archive & arc);

    static const rapidjson::Type SerializingType() 
    {
        return rapidjson::Type::kObjectType;
    }
};

template <>
struct Serializer<ildhal::CircleShape>
{
    static void Serialize(ildhal::CircleShape & shape, Archive & arc);

    static const rapidjson::Type SerializingType() 
    {
        return rapidjson::Type::kObjectType;
    }
};

}

GENERATE_ABSTRACT_CLASS_CONSTRUCTOR(ildhal::Shape)

#endif
