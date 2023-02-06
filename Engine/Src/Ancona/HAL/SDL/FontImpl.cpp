#include <SDL2/SDL_ttf.h>

#include <Ancona/HAL/SDL/FontImpl.hpp>
#include <Ancona/System/Log.hpp>

namespace ildhal
{

/* Pimpl Implementation */

bool priv::FontImpl::LoadSDLFontFromFile(const std::string & filename)
{
    TTF_Font * loadedFont = TTF_OpenFont(filename.c_str(), 28);

    if (!loadedFont)
    {
        ILD_Log("Failed to load ttf font!: " << filename << "\nSDL_ttf error: " << TTF_GetError());
        return false;
    }

    _sdlFont = std::unique_ptr<TTF_Font, SDL_FontDestructor>(loadedFont);

    return true;
}

/* HAL Interface Implementation */

Font::Font() : _pimpl(std::make_unique<priv::FontImpl>())
{
}

bool Font::LoadFromFile(const std::string & filename, ildhal::RenderTarget & renderTarget)
{
    return fontImpl().LoadSDLFontFromFile(filename);
}

} // namespace ildhal
