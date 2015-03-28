#include <Ancona/Engine/Loading/PolymorphicMap.hpp>

using namespace ild;

PolymorphicSerializer * PolymorphicMap::GetSerializer(const std::string & name)
{ 
    return _serializers[name].get(); 
}

void PolymorphicMap::RegisterType(const std::string & name, std::type_index type, PolymorphicSerializer * serializer)
{
        _typeToName[type] = name;
        _serializers[name] = std::unique_ptr<PolymorphicSerializer>(serializer);
}

