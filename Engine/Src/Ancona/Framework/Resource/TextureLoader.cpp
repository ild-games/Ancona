#include <Ancona/Framework/Resource/TextureLoader.hpp>

using namespace ild;

TextureLoader::TextureLoader(const std::string &resourceName, const std::string &fileExtension)
    : HalResourceLoader<ildhal::Texture>(resourceName, fileExtension)
{
}
