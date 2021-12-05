// Altered SFML CircleShape.hpp for Ancona's HAL abstraction layer

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

#ifndef Ancona_HAL_CircleShape_H_
#define Ancona_HAL_CircleShape_H_

#include <Ancona/HAL/Shape.hpp>

namespace ildhal
{

namespace priv
{
class CircleShapeImpl;
}

class CircleShape : public Shape
{
  public:
    CircleShape();

    void radius(float radius);
    float radius() const;

    /* getters and setters */
    priv::CircleShapeImpl &circleShapeImpl() const;
};

} // namespace ildhal

#endif