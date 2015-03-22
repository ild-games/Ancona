#ifndef Ancona_Engine_Loading_Serializer_H_
#define Ancona_Engine_Loading_Serializer_H_

namespace ild
{

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
};

}

#endif
