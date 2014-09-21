#include <Ancona/Engine/Resource/AbstractLoader.hpp>

using namespace ild;

AbstractLoader::AbstractLoader(const std::string & resourceName, 
        const std::type_index & resourceType) :
    _resourceName(resourceName), _resourceType(resourceType)
{
     
}

const std::type_index & AbstractLoader::GetResourceType()
{
    return _resourceType;
}

const std::string & AbstractLoader::GetResourceName()
{
    return _resourceName;
}
