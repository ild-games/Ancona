#include <SDL2_image/SDL_image.h>

#include <Ancona/HAL/SDL/RenderTargetImpl.hpp>
#include <Ancona/HAL/SDL/TextureImpl.hpp>
#include <Ancona/System/Log.hpp>

namespace ildhal
{

/* Pimpl Implementation */

bool priv::TextureImpl::LoadSDLTextureFromFile(const std::string & filename, SDL_Renderer & sdlRenderer)
{
    SDL_Surface * loadedSurface = IMG_Load(filename.c_str());
    if (loadedSurface == nullptr)
    {
        ILD_Log("Failed to create SDL_Surface for texture!: " << filename);
        return false;
    }

    SDL_Texture * texture = SDL_CreateTextureFromSurface(&sdlRenderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
    if (texture == nullptr)
    {
        ILD_Log("Failed to create SDL_Texture from surface!: " << filename);
        return false;
    }

    ILD_Log("Successfully loaded texture!: " << filename);
    _sdlTexture = std::unique_ptr<SDL_Texture, SDL_TextureDestructor>(texture);

    return true;
}

/* HAL Interface Implementation */

Texture::Texture() : _pimpl(std::make_unique<priv::TextureImpl>())
{
}

bool Texture::LoadFromFile(const std::string & filename, ildhal::RenderTarget & renderTarget)
{
    return textureImpl().LoadSDLTextureFromFile(filename, renderTarget.renderTargetImpl().sdlRenderer());
}

/* getters and setters */

void Texture::repeated(bool newRepeated)
{
}

ild::Vector2u Texture::size() const
{
    return ild::Vector2u(0, 0);
}

void Texture::smooth(bool newSmooth)
{
}

bool Texture::smooth() const
{
    return true;
}

} // namespace ildhal
