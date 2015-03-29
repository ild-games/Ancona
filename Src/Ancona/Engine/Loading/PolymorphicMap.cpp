#include <Ancona/Engine/Loading/PolymorphicMap.hpp>

using namespace ild;

std::unordered_map<std::type_index, std::string> PolymorphicMap::_typeToName;
std::unordered_map<std::string, std::unique_ptr<PolymorphicSerializer>> PolymorphicMap::_serializers;

PolymorphicSerializer * PolymorphicMap::GetSerializer(const std::string & name)
{ 
    return _serializers[name].get(); 
}

void PolymorphicMap::RegisterType(const std::string & name, std::type_index type, PolymorphicSerializer * serializer)
{
    _typeToName[type] = name;
    _serializers[name] = std::unique_ptr<PolymorphicSerializer>(serializer);
}

