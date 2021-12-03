#ifndef ANCONA_Engine_Serializer_UtilSerializer_H
#define ANCONA_Engine_Serializer_UtilSerializer_H

#include <Ancona/Framework/Serializing/Archive.hpp>
#include <Ancona/Framework/Serializing/HalSerializer.hpp>
#include <Ancona/Framework/Serializing/Serializer.hpp>
#include <Ancona/Framework/Serializing/StdSerializer.hpp>
#include <Ancona/Graphics/Color.hpp>
#include <Ancona/Graphics/Rect.hpp>
#include <Ancona/Util/Vector2.hpp>
#include <Ancona/Util/Vector3.hpp>
#include <Ancona/Util2D/Collision/Box2.hpp>

namespace ild
{

template <> struct Serializer<Vector2f>
{
    static void Serialize(Vector2f &property, Archive &arc)
    {
        arc(property.x, "x");
        arc(property.y, "y");
    }

    static const rapidjson::Type SerializingType()
    {
        return rapidjson::Type::kObjectType;
    }
};

template <> struct Serializer<Vector3f>
{
    static void Serialize(Vector3f &property, Archive &arc)
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

template <> struct Serializer<Box2>
{
    static void Serialize(Box2 &property, Archive &arc)
    {
        arc(property.Dimension, "dimension");
        arc(property.Position, "position");
        arc(property.Rotation, "rotation");
    }

    static const rapidjson::Type SerializingType()
    {
        return rapidjson::Type::kObjectType;
    }
};

template <> struct Serializer<IntRect>
{
    static void Serialize(IntRect &rect, Archive &arc)
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

template <> struct Serializer<Color>
{
    static void Serialize(Color &property, Archive &arc)
    {
        arc(property.r, "r");
        arc(property.g, "g");
        arc(property.b, "b");
        arc(property.a, "a");
    }

    static const rapidjson::Type SerializingType()
    {
        return rapidjson::Type::kObjectType;
    }
};

} // namespace ild

#endif
