#include <Ancona/Framework/Resource/SoundBufferLoader.hpp>

using namespace ild;

SoundBufferLoader::SoundBufferLoader(
        const std::string & resourceName, 
        const std::string & fileExtension) :
    HalResourceLoader<ildhal::SoundBuffer>(resourceName, fileExtension)
{
}
