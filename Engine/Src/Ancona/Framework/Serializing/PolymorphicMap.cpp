#include <Ancona/Framework/Serializing/PolymorphicMap.hpp>

using namespace ild;

std::unordered_map<std::type_index, std::string> * PolymorphicMap::_typeToName;
std::unordered_map<std::string, std::unique_ptr<PolymorphicSerializer>> * PolymorphicMap::_serializers;

PolymorphicSerializer * PolymorphicMap::serializer(const std::string &name)
{
    if (_serializers->find(name) != _serializers->end())
    {
        return (*_serializers)[name].get(); 
    }
    return nullptr;
}

void PolymorphicMap::RegisterType(const std::string & name, std::type_index type, PolymorphicSerializer * serializer)
{
    static bool shouldInitMaps = true;
    if (shouldInitMaps)
    {
        _typeToName = new std::unordered_map<std::type_index, std::string>();
        _serializers = new std::unordered_map<std::string, std::unique_ptr<PolymorphicSerializer>>();
        shouldInitMaps = false;
    }
    (*_typeToName)[type] = name;
    (*_serializers)[name] = std::unique_ptr<PolymorphicSerializer>(serializer);
}
