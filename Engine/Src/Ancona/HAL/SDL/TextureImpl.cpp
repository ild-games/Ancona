
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include <Ancona/HAL/SDL/RenderTargetImpl.hpp>
#include <Ancona/HAL/SDL/TextureImpl.hpp>
#include <Ancona/System/Log.hpp>

namespace ildhal
{

/* Pimpl Implementation */

bool priv::TextureImpl::LoadSDLTextureFromFile(const std::string & filename, SDL_Renderer & sdlRenderer)
{
    SDL_IOStream * rwops = SDL_IOFromFile(filename.c_str(), "rb");
    if (rwops == nullptr)
    {
        ILD_Log("Failed to create SDL_IOStream for texture!: " << filename << "\nSDL error: " << SDL_GetError());
        return false;
    }
    SDL_Surface * loadedSurface = IMG_Load_IO(rwops, 1);
    if (loadedSurface == nullptr)
    {
        ILD_Log("Failed to create SDL_Surface for texture!: " << filename << "\nSDL_image error: " << SDL_GetError());
        return false;
    }

    SDL_Texture * texture = SDL_CreateTextureFromSurface(&sdlRenderer, loadedSurface);
    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_LINEAR);
    SDL_DestroySurface(loadedSurface);
    if (texture == nullptr)
    {
        ILD_Log("Failed to create SDL_Texture from surface!: " << filename << "\nSDL error: " << SDL_GetError());
        return false;
    }

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
    SDL_Texture * texture = &textureImpl().sdlTexture();
    float w = 0;
    float h = 0;

    SDL_GetTextureSize(texture, &w, &h);
    return ild::Vector2u((int)w, (int)h);
}

void Texture::smooth(bool newSmooth)
{
}

bool Texture::smooth() const
{
    return true;
}

} // namespace ildhal
