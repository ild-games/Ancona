#ifndef Ancona_Engine_Serializing_Serializer_H_
#define Ancona_Engine_Serializing_Serializer_H_

#include <Ancona/Util/Algorithm/Types.hpp>
#include <Ancona/Util/Json.hpp>

namespace ild
{

GENERATE_METHOD_TESTER(Serialize);

class Archive;

/**
 * @brief The default serializer which will call serialize on the property object.
 *
 * @tparam T Type of the property object.
 *
 * @author Tucker Lein
 * @author Jeff Swenson
 */
template <class T>
struct Serializer
{
    /**
     * @brief Used to call serialize on the property.
     *
     * @param property Property being serialized.
     * @param arc Archive instance.
     */
    static void Serialize(T & property, Archive & arc)
    {
        property.Serialize(arc);
    }

    static const rapidjson::Type SerializingType() 
    {
        return rapidjson::Type::kObjectType;
    }
};

}

#endif
