#ifndef Ancona_Engine_Loading_PolymorphicRegistration_H_
#define Ancona_Engine_Loading_PolymorphicRegistration_H_

#include <string>

#include <Ancona/Engine/Loading/Archive.hpp>
#include <Ancona/Engine/Loading/PolymorphicSerializer.hpp>

#define REGISTER_POLYMORPHIC_SERIALIZER(CLASS)                           \
    template<> const std::string ild::PolymorphicTypeKey<CLASS>::Key =   \
        PolymorphicRegistration::RegisterType<CLASS>(#CLASS);            \

namespace ild
{


template <class T>
class PolymorphicSerializerImpl : public PolymorphicSerializer
{
    public:

        /**
         * @copydoc ild::PolymorphicSerializer::Serialize()
         */
        void Serialize(void *& property, Archive & arc) override
        {
            T *& typedProp = (T *&)(property);
            if(arc.IsLoading())
            {
                typedProp = new T();
            }
            Serializer<T>::Serialize(*typedProp, arc);
        }
};

namespace PolymorphicRegistration
{
    /**
     * @brief Saves a mapping between the string name and the type.
     *
     * @tparam T Type being registered
     * @param name Name representing the type.
     *
     * @return The name representing the type.
     */
    template <class T>
    std::string static RegisterType(const std::string & name)
    {
        PolymorphicMap::RegisterType(
                name,
                std::type_index(typeid(T)),
                new PolymorphicSerializerImpl<T>()
                );
        return name;
    }
}

}


#endif 
