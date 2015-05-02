#ifndef Ancona_Engine_Serializing_PolymorphicMap_H_
#define Ancona_Engine_Serializing_PolymorphicMap_H_

#include <memory>
#include <string>
#include <typeindex>
#include <unordered_map>

#include <Ancona/Framework/Serializing/PolymorphicSerializer.hpp>

namespace ild
{

template <class T>
struct PolymorphicTypeKey
{
    static const std::string Key;
};

/**
 * @brief Keeps a map that is used to serialize polymorphic types.
 *
 * @author Jeff Swenson
 * @author Tucker Lein
 */
class PolymorphicMap
{
    public:
        /**
         * @brief Saves a mapping between the string name and the type.
         *
         * @param name Name representing the type.
         * @param type Actual type being registered.
         * @param serializer Serializer used to save and load the type.
         */
        static void RegisterType(const std::string & name, std::type_index type, PolymorphicSerializer * serializer);

        /* getters and setters */
        static PolymorphicSerializer * serializer(const std::string &name);

        template <class T>
        static PolymorphicSerializer * serializer(T *object)
        { 
            if (_typeToName->find(typeid(object)) != _typeToName->end())
            {
                return _serializers->at(_typeToName->at(typeid(object))).get(); 
            }
            return nullptr;
        }

    private:
        static std::unordered_map<std::type_index, std::string> * _typeToName;
        static std::unordered_map<std::string, std::unique_ptr<PolymorphicSerializer>> * _serializers;
};

}

#endif
