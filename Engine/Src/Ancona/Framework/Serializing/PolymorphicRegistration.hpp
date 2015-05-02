#ifndef Ancona_Engine_Serializing_PolymorphicRegistration_H_
#define Ancona_Engine_Serializing_PolymorphicRegistration_H_

#include <string>

#include <Ancona/Framework/Serializing/Archive.hpp>
#include <Ancona/Framework/Serializing/ClassConstructor.hpp>
#include <Ancona/Framework/Serializing/PolymorphicSerializer.hpp>
#include <Ancona/Util/Assert.hpp>

//TODO ANC-72 Update the these registration macros
/**
 * @brief Called to register a polymorphic class that can be serialized by the
 * loading framework.
 *
 * Example:
 * REGISTER_POLYMORPHIC_SERIALIZER(ild::ShapeDrawable)
 *
 */
#define REGISTER_POLYMORPHIC_SERIALIZER(CLASS)                           \
    template<> const std::string ild::PolymorphicTypeKey<CLASS>::Key =   \
        PolymorphicRegistration::RegisterType<CLASS>(#CLASS);

/**
 * @brief Called to register an abstract base class whose children can be serialized
 * by the loading framework.
 *
 * Example:
 * REGISTER_POLYMORPHIC_SERIALIZER(ild::Drawable)
 */
#define REGISTER_POLYMORPHIC_SERIALIZER_ABSTRACT_BASE(CLASS)             \
    template <> const std::string ild::PolymorphicTypeKey<CLASS>::Key =  \
        PolymorphicRegistration::RegisterAbstractType<CLASS>(#CLASS);


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
            if(arc.loading())
            {
                typedProp = new T();
            }
            Serializer<T>::Serialize(*typedProp, arc);
        }
};

/**
 * @brief Used to provide a map entry for abstract bases of polymorphic types.
 * @author Jeff Swenson
 */
class PolymorphicSerializerAbstractBase : public PolymorphicSerializer
{
    public:
         PolymorphicSerializerAbstractBase(std::string className);
        /**
         * @copydoc ild::PolymorphicSerializer::Serialize()
         */
        void Serialize(void *& property, Archive & arc) override;
    private:
        std::string _className;

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

    /**
     * @brief Saves a mapping between the string name and an abstract type.
     *
     * @tparam T Type being registered
     * @param name Name representing the type.
     *
     * @return The name representing the type.
     */
    template <class T>
    std::string static RegisterAbstractType(const std::string & name)
    {
        PolymorphicMap::RegisterType(
                name,
                std::type_index(typeid(T)),
                new PolymorphicSerializerAbstractBase(name)
        );
        return name;
    }
}


}


#endif 
