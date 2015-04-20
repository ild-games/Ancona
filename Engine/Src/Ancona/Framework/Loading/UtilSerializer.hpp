#ifndef ANCONA_UTILSERIALIZER_H
#define ANCONA_UTILSERIALIZER_H

#include <Ancona/Framework/Loading/Archive.hpp>
#include <Ancona/Framework/Loading/Serializer.hpp>
#include <Ancona/Framework/Loading/SFMLSerializer.hpp>
#include <Ancona/Framework/Loading/StdSerializer.hpp>
#include <Ancona/Util2D/Collision/Box2.hpp>

namespace ild {

template<>
struct Serializer<Box2>
{
    static void Serialize(Box2 & property, Archive & arc) {
        arc(property.Dimension, "dimension");
        arc(property.Position, "position");
        arc(property.Rotation, "rotation");
    }
};

}


#endif
