#ifndef ANCONA_Engine_Serializer_UtilSerializer_H
#define ANCONA_Engine_Serializer_UtilSerializer_H

#include <Ancona/Framework/Serializing/Archive.hpp>
#include <Ancona/Framework/Serializing/Serializer.hpp>
#include <Ancona/Framework/Serializing/SFMLSerializer.hpp>
#include <Ancona/Framework/Serializing/StdSerializer.hpp>
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
