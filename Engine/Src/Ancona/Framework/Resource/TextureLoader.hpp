#pragma once

#include <Ancona/Framework/Resource/HalResourceLoader.hpp>
#include <Ancona/HAL.hpp>

namespace ild
{

/**
 * @brief Texture loader is used to load an ildhal::Texture
 *
 * @author Jeff Swenson
 */
class TextureLoader : public HalResourceLoader<ildhal::Texture>
{
  public:
    /**
     * @brief Initialize a texture loader and register it with the ResourceLibrary
     *
     * @param resourceName Resource Type to be used (EX "TextureJPEG")
     * @param fileExtension File extension to be used (EX "jpeg")
     */
    TextureLoader(const std::string & resourceName, const std::string & fileExtension);
};

} // namespace ild
