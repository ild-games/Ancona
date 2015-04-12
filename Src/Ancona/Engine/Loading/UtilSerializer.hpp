//
// Created by jeff on 4/10/15.
//

#ifndef ANCONA_UTILSERIALIZER_H
#define ANCONA_UTILSERIALIZER_H

#include <Ancona/Engine/Loading/Serializer.hpp>
#include <Ancona/Engine/Loading/StdSerializer.hpp>
#include <Ancona/Engine/Loading/SFMLSerializer.hpp>
#include <Ancona/Engine/Loading/Archive.hpp>

#include <Ancona/Util/Collision/Box2.hpp>

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


#endif //ANCONA_UTILSERIALIZER_H
