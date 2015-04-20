#include <Ancona/Framework/Resource/AbstractLoader.hpp>
#include <Ancona/Framework/Resource/ResourceLibrary.hpp>

using namespace ild;

AbstractLoader::AbstractLoader(
        const std::string & resourceName,
        const std::type_index & resourceType) :
    _resourceName(resourceName),
    _resourceType(resourceType)
{
    ResourceLibrary::RegisterLoader(this);
}

std::string AbstractLoader::GetResourceFileName(
        const std::string & resourceDir,
        const std::string & resourceKey,
        const std::string & fileExtension)
{
    return ResourceLibrary::ResourceRoot() + "/" +
           resourceDir + "/" +
           resourceKey + "." + fileExtension;
}
