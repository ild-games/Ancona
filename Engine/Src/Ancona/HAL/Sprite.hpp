// Altered SFML Sprite.hpp for Ancona's HAL abstraction layer

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

#ifndef Ancona_HAL_Sprite_H_
#define Ancona_HAL_Sprite_H_

#include <Ancona/Graphics/Color.hpp>
#include <Ancona/Graphics/Rect.hpp>
#include <Ancona/HAL/Drawable.hpp>

namespace ildhal
{

class Texture;

namespace priv
{
class SpriteImpl;
}

class Sprite : public Drawable
{
  public:
    Sprite();
    Sprite(const Texture &texture, const ild::IntRect &rectangle);

    /* getters and setters */
    void origin(const ild::Vector2f &newOrigin);
    void origin(float x, float y);
    const ild::Color color() const;
    void color(const ild::Color &newColor);
    void texture(const Texture &newTexture, bool resetRect = false);

    priv::SpriteImpl &spriteImpl() const;
};

} // namespace ildhal

#endif
