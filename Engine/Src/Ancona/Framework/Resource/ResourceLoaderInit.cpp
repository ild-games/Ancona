#include <Ancona/Framework/Resource/ResourceLoaderInit.hpp>

using namespace ild;

TextureLoader* _jpegTextureLoader = nullptr;
TextureLoader* _pngTextureLoader = nullptr;
FontLoader* _ttfFontLoader = nullptr;
SoundBufferLoader* _wavSoundBufferLoader = nullptr;

void ResourceLoaderInit::Init()
{
    _jpegTextureLoader = new TextureLoader("TextureJPEG", "jpeg");
    _pngTextureLoader = new TextureLoader("TexturePNG", "png");
    _ttfFontLoader = new FontLoader("FontTTF", "ttf");
    _wavSoundBufferLoader = new SoundBufferLoader("SoundWAV", "wav");
}

void ResourceLoaderInit::Destroy()
{
    if (_jpegTextureLoader != nullptr) {
        delete _jpegTextureLoader;
    }

    if (_pngTextureLoader != nullptr) {
        delete _pngTextureLoader;
    }

    if (_ttfFontLoader != nullptr) {
        delete _ttfFontLoader;
    }

    if (_wavSoundBufferLoader != nullptr) {
        delete _wavSoundBufferLoader;
    }
}
