// Altered SFML RectangleShape.hpp for Ancona's HAL abstraction layer

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

#pragma once

#include <Ancona/Graphics/Rect.hpp>
#include <Ancona/HAL/Shape.hpp>
#include <Ancona/Util/Vector2.hpp>

namespace ildhal
{

namespace priv
{
class RectangleShapeImpl;
}

class RectangleShape : public Shape
{
  public:
    RectangleShape();
    explicit RectangleShape(const ild::Vector2f & size);

    void Draw(ildhal::RenderTarget & renderTarget, const ildhal::RenderStates & renderStates) override;

    /* getters and setters */
    const ild::Vector2f size() const;
    void size(const ild::Vector2f & newSize);
    ild::FloatRect localBounds() const override;

    priv::RectangleShapeImpl & rectangleShapeImpl() const;
};

} // namespace ildhal
