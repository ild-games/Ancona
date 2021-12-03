#include <Ancona/HAL/SFML/TextureImpl.hpp>

namespace ildhal
{

/* Pimpl Implementation */

priv::TextureImpl::TextureImpl()
{
    _sfmlTexture = new sf::Texture();
}

priv::TextureImpl::~TextureImpl()
{
    delete _sfmlTexture;
}

/* HAL Interface Implementation */

Texture::Texture() : _pimpl(std::make_unique<priv::TextureImpl>())
{
}

bool Texture::LoadFromFile(const std::string &filename)
{
    return textureImpl().sfmlTexture().loadFromFile(filename);
}

/* getters and setters */

void Texture::repeated(bool newRepeated)
{
    textureImpl().sfmlTexture().setRepeated(newRepeated);
}

ild::Vector2u Texture::size() const
{
    auto sfmlSize = textureImpl().sfmlTexture().getSize();
    return ild::Vector2u(sfmlSize.x, sfmlSize.y);
}

void Texture::smooth(bool newSmooth)
{
    textureImpl().sfmlTexture().setSmooth(newSmooth);
}

bool Texture::smooth() const
{
    return textureImpl().sfmlTexture().isSmooth();
}

} // namespace ildhal
