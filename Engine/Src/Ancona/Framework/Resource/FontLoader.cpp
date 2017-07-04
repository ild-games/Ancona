#include <Ancona/Framework/Resource/FontLoader.hpp>

using namespace ild;

FontLoader::FontLoader(
        const std::string & resourceName, 
        const std::string & fileExtension) :
    SFMLResourceLoader<sf::Font>(resourceName, fileExtension)
{
}
