#ifndef Ancona_Engine_Resource_TextureLoader_H_
#define Ancona_Engine_Resource_TextureLoader_H_

#include <SFML/Graphics.hpp>

#include <Ancona/Framework/Resource/SFMLResourceLoader.hpp>

namespace ild
{

/**
 * @brief Texture loader is used to load an sf::Texture
*
 * @author Jeff Swenson
 */
class TextureLoader : public SFMLResourceLoader<sf::Texture>
{
    public:
        /**
         * @brief Initialize a texture loader and register it with the ResourceLibrary
         *
         * @param resourceName Resource Type to be used (EX "TextureJPEG")
         * @param fileExtension File extension to be used (EX "jpeg")
         */
        TextureLoader(
                const std::string & resourceName,
                const std::string & fileExtension);
};

}


#endif
