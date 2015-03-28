#ifndef Ancona_Engine_Loading_PolymorphicRegistration_H_
#define Ancona_Engine_Loading_PolymorphicRegistration_H_

#include <Ancona/Engine/Loading/Archive.hpp>
#include <Ancona/Engine/Loading/PolymorphicSerializer.hpp>

#define REGISTER_POLYMORPHIC_SERIALIZER(CLASS)                                           \
    ild::PolymorphicTypeKey<CLASS>::Key =                                                \
        PolymorphicRegistration::RegisterType<CLASS>(#CLASS);                            \

namespace ild
{


template <class T>
class PolymorphicSerializerImpl
{
    public:

        /**
         * @copydoc ild::PolymorphicSerializer::Serialize()
         */
        void Serialize(void *& property, Archive & arc) override
        {
            T *& typedProp = static_cast<T *&>(property);
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
