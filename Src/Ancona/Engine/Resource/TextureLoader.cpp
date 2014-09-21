#include <Ancona/Engine/Resource/TextureLoader.hpp>

using namespace ild;

TextureLoader::TextureLoader(
        const std::string & resourceName, 
        const std::string & fileExtension,
        const std::string & directory = std::string("texture"))
        : SFMLResourceLoader<sf::Texture>(resourceName,fileExtension,directory)
{

}
