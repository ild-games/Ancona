#ifndef Ancona_Engine_Resource_FontLoader_H_
#define Ancona_Engine_Resource_FontLoader_H_

#include <Ancona/Engine/Resource/SFMLResourceLoader.hpp>

#include <SFML/Graphics.hpp>

namespace ild
{

/**
 * @brief  Font loader is used to load an sf::Font
 *
 * @author Tucker Lein
 */
class FontLoader: public SFMLResourceLoader<sf::Font>
{
    public:
        /**
         * @brief Initialize a font loader and register it with the ResourceLibrary
         *
         * @param resourceName Resource Type to be used (EX "FontTTF")
         * @param fileExtension File extension to be used (EX "ttf")
         * @param directory Directory that resources are stored in (Defaults to "font")
         */
        FontLoader(
                const std::string & resourceName,
                const std::string & fileExtension,
                const std::string & directory = std::string("font"));
};

}

#endif
