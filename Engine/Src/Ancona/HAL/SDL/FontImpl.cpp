#include <Ancona/HAL/SDL/FontImpl.hpp>

namespace ildhal
{

/* Pimpl Implementation */

priv::FontImpl::FontImpl() : _sfmlFont(std::make_unique<sf::Font>())
{
}

/* HAL Interface Implementation */

Font::Font() : _pimpl(std::make_unique<priv::FontImpl>())
{
}

bool Font::LoadFromFile(const std::string & filename, ildhal::RenderTarget & renderTarget)
{
    return fontImpl().sfmlFont().loadFromFile(filename);
}

} // namespace ildhal