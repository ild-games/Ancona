// Altered SFML View.cpp for Ancona's namespace

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

#include <cmath>

#include <Ancona/Graphics/View.hpp>
#include <Ancona/System/Log.hpp>

namespace ild
{

View::View() : _viewport(0, 0, 1, 1)
{
    Reset(FloatRect(0, 0, 1000, 1000));
}

View::View(const FloatRect & rectangle) : _viewport(0, 0, 1, 1)
{
    Reset(rectangle);
}

View::View(const Vector2f & center, const Vector2f & size) : _viewport(0, 0, 1, 1)
{
    Reset(FloatRect(center.x - (size.x / 2.0f), center.y - (size.y / 2.0f), size.x, size.y));
}

void View::Reset(const FloatRect & rectangle)
{
    _transform = Transform();
    rotation(0.0f);
    size(rectangle.width, rectangle.height);
    center(rectangle.left + rectangle.width / 2.f, rectangle.top + rectangle.height / 2.f);
    Zoom(1.0f);
}

void View::Move(float offsetX, float offsetY)
{
    center(_center.x + offsetX, _center.y + offsetY);
}

void View::Move(const Vector2f & offset)
{
    center(_center + offset);
}

void View::Rotate(float angle)
{
    rotation(_rotation + angle);
}

void View::Zoom(float factor)
{
    _transform.scale(factor, factor);
    size(_size.x * factor, _size.y * factor);
}

/* getters and setters */

void View::center(const Vector2f & centerPoint)
{
    center(centerPoint.x, centerPoint.y);
}

void View::center(float x, float y)
{
    _transform.position(x, y);

    _center.x = x;
    _center.y = y;
}

void View::size(const Vector2f & newSize)
{
    size(newSize.x, newSize.y);
}

void View::size(float width, float height)
{
    _transform.origin(width / 2.0f, height / 2.0f);

    _size.x = width;
    _size.y = height;
}

void View::rotation(float angle)
{
    _transform.rotation(angle);

    _rotation = static_cast<float>(fmod(angle, 360));
    if (_rotation < 0)
    {
        _rotation += 360.f;
    }
}

} // namespace ild
