#include <Ancona/Framework/Resource/AbstractLoader.hpp>
#include <Ancona/Framework/Resource/ResourceLibrary.hpp>
#include <Ancona/System/Log.hpp>
#include <sstream>

using namespace ild;

AbstractLoader::AbstractLoader(const std::string &resourceName, const std::type_index &resourceType)
    : _resourceName(resourceName), _resourceType(resourceType)
{
    ResourceLibrary::RegisterLoader(this);
}

std::string AbstractLoader::GetResourceFileName(const std::string &resourceKey, const std::string &fileExtension)
{
    auto resourceRoot = ResourceLibrary::ResourceRoot();
    std::stringstream stream;
    stream << resourceRoot << "/" << resourceKey << "." << fileExtension;
    return stream.str();
}
