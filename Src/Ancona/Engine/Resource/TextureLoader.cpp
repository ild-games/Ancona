#include <Ancona/Engine/Resource/TextureLoader.hpp>
#include <SFMLGraphics>

using namespace ild;

TextureLoader::TextureLoader() :
    AbstractLoader("texture", typeid(sf::Texture))
{
    ResourceLibrary::RegisterLoader(this);
}

void * TextureLoader::Load(const std::string & resourceKey) 
{
    
}

void * TextureLoader::DeleteResource(void * resource)
{

}
