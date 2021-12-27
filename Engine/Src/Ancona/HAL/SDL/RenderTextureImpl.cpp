#include <Ancona/HAL/SDL/RenderTextureImpl.hpp>

namespace ildhal
{

/* Pimpl Implementation */

/* HAL Interface Implementation */

RenderTexture::RenderTexture()
{
    _pimpl = std::make_unique<priv::RenderTextureImpl>();
}

void RenderTexture::Display()
{
}

bool RenderTexture::Create(unsigned int width, unsigned int height)
{
    return true;
}

/* getters and setters */
ild::Vector2u RenderTexture::size() const
{
    return ild::Vector2u(0, 0);
}

void RenderTexture::smooth(bool newSmooth)
{
}

priv::RenderTextureImpl & RenderTexture::renderTextureImpl() const
{
    return static_cast<priv::RenderTextureImpl &>(*_pimpl);
}

} // namespace ildhal
