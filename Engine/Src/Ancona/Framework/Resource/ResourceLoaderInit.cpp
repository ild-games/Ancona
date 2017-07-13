#include <Ancona/Framework/Resource/ResourceLoaderInit.hpp>

#include <Ancona/Framework/Resource/TextureLoader.hpp>
#include <Ancona/Framework/Resource/FontLoader.hpp>
#include <Ancona/Framework/Resource/SoundBufferLoader.hpp>

using namespace ild;

void ResourceLoaderInit::Init()
{
    new TextureLoader("TextureJPEG", "jpeg");
    new TextureLoader("TexturePNG", "png");
    new FontLoader("FontTTF", "ttf");
    new SoundBufferLoader("SoundWAV", "wav");
}
