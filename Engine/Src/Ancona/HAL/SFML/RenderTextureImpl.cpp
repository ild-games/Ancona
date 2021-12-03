// Altered SFML RenderTexture.cpp for Ancona's HAL abstraction layer

////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2018 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#include <SFML/Graphics.hpp>

#include <Ancona/HAL/SFML/RenderTextureImpl.hpp>

namespace ildhal
{

/* Pimpl Implementation */

priv::RenderTextureImpl::RenderTextureImpl()
{
    _sfmlRenderTarget = std::make_unique<sf::RenderTexture>();
}

sf::RenderTexture &priv::RenderTextureImpl::sfmlRenderTexture() const
{
    return static_cast<sf::RenderTexture &>(*_sfmlRenderTarget);
}

/* HAL Interface Implementation */

RenderTexture::RenderTexture()
{
    _pimpl = std::make_unique<priv::RenderTextureImpl>();
}

void RenderTexture::Display()
{
    renderTextureImpl().sfmlRenderTexture().display();
}

bool RenderTexture::Create(unsigned int width, unsigned int height)
{
    return renderTextureImpl().sfmlRenderTexture().create(width, height);
}

/* getters and setters */
ild::Vector2u RenderTexture::size() const
{
    auto sfmlSize = renderTextureImpl().sfmlRenderTexture().getSize();
    return ild::Vector2u(sfmlSize.x, sfmlSize.y);
}

void RenderTexture::smooth(bool newSmooth)
{
    renderTextureImpl().sfmlRenderTexture().setSmooth(newSmooth);
}

// const Texture& RenderTexture::texture() const
// {
//     return
// }

priv::RenderTextureImpl &RenderTexture::renderTextureImpl() const
{
    return static_cast<priv::RenderTextureImpl &>(*_pimpl);
}

} // namespace ildhal
