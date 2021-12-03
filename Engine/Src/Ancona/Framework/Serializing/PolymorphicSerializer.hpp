#ifndef Ancona_Engine_Serializing_PolymorphicSerializer_H_
#define Ancona_Engine_Serializing_PolymorphicSerializer_H_

namespace ild
{

class Archive;

/**
 * @brief Serializer used to serialize in polymorphic types.
 *
 * @author Jeff Swenson
 * @author Tucker Lein
 */
class PolymorphicSerializer
{
  public:
    /**
     * @brief Serializes polymorphic types.
     *
     * @param property Property being serialized.
     * @param arc Archive instance
     */
    virtual void Serialize(void *&property, Archive &arc) = 0;
};

} // namespace ild

#endif
