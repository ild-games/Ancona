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

std::istream * AbstractLoader::OpenResource(
        const std::string & resourceDir, 
        const std::string & resourceKey, 
        const std::string & fileExtension)
{
    std::string filepath = 
        ResourceLibrary::ResourceRoot() + "/" + 
        resourceDir + "/" +
        resourceKey + "." + fileExtension;
    return new std::ifsteam(filepath.c_str());
}

void AbstractLoader::CloseResource(std::istream * openStream)
{
    openStream->close();
    delete openStream;
}


