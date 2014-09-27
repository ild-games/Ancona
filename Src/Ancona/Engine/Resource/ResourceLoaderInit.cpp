#include <Ancona/Engine/Resource/ResourceLoaderInit.hpp>

#include <Ancona/Engine/Resource/TextureLoader.hpp>

using namespace ild;

void ResourceLoaderInit::Init()
{
    new TextureLoader("TextureJPEG", "jpeg");
    new TextureLoader("TexturePNG", "png");
}
