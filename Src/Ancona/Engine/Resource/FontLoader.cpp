#include <Ancona/Engine/Resource/FontLoader.hpp>

using namespace ild;

FontLoader::FontLoader(
        const std::string & resourceName, 
        const std::string & fileExtension,
        const std::string & directory)
    : SFMLResourceLoader<sf::Font>(resourceName, fileExtension, directory)
{
}
