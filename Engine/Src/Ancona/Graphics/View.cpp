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

#include <Ancona/Graphics/View.hpp>
#include <cmath>

using namespace ild;

View::View()
    : _center(), _size(), _rotation(0), _viewport(0, 0, 1, 1), _transformUpdated(false), _invTransformUpdated(false)
{
    Reset(FloatRect(0, 0, 1000, 1000));
}

View::View(const FloatRect &rectangle)
    : _center(), _size(), _rotation(0), _viewport(0, 0, 1, 1), _transformUpdated(false), _invTransformUpdated(false)
{
    Reset(rectangle);
}

View::View(const Vector2f &center, const Vector2f &size)
    : _center(center), _size(size), _rotation(0), _viewport(0, 0, 1, 1), _transformUpdated(false),
      _invTransformUpdated(false)
{
}

void View::Reset(const FloatRect &rectangle)
{
    _center.x = rectangle.left + rectangle.width / 2.f;
    _center.y = rectangle.top + rectangle.height / 2.f;
    _size.x = rectangle.width;
    _size.y = rectangle.height;
    _rotation = 0;

    _transformUpdated = false;
    _invTransformUpdated = false;
}

void View::Move(float offsetX, float offsetY)
{
    center(_center.x + offsetX, _center.y + offsetY);
}

void View::Move(const Vector2f &offset)
{
    center(_center + offset);
}

void View::Rotate(float angle)
{
    rotation(_rotation + angle);
}

void View::Zoom(float factor)
{
    size(_size.x * factor, _size.y * factor);
}

const Transform &View::InverseTransform() const
{
    // Recompute the matrix if needed
    if (!_invTransformUpdated)
    {
        _inverseTransform = transform().Inverse();
        _invTransformUpdated = true;
    }

    return _inverseTransform;
}

/* getters and setters */

void View::center(float x, float y)
{
    _center.x = x;
    _center.y = y;

    _transformUpdated = false;
    _invTransformUpdated = false;
}

void View::center(const Vector2f &centerPoint)
{
    center(centerPoint.x, centerPoint.y);
}

void View::size(float width, float height)
{
    _size.x = width;
    _size.y = height;

    _transformUpdated = false;
    _invTransformUpdated = false;
}

void View::size(const Vector2f &newSize)
{
    size(newSize.x, newSize.y);
}

void View::rotation(float angle)
{
    _rotation = static_cast<float>(fmod(angle, 360));
    if (_rotation < 0)
    {
        _rotation += 360.f;
    }

    _transformUpdated = false;
    _invTransformUpdated = false;
}

const Transform &View::transform() const
{
    // Recompute the matrix if needed
    if (!_transformUpdated)
    {
        // Rotation components
        float angle = _rotation * 3.141592654f / 180.f;
        float cosine = static_cast<float>(std::cos(angle));
        float sine = static_cast<float>(std::sin(angle));
        float tx = -_center.x * cosine - _center.y * sine + _center.x;
        float ty = _center.x * sine - _center.y * cosine + _center.y;

        // Projection components
        float a = 2.f / _size.x;
        float b = -2.f / _size.y;
        float c = -a * _center.x;
        float d = -b * _center.y;

        // Rebuild the projection matrix
        _transform = Transform(a * cosine, a * sine, a * tx + c, -b * sine, b * cosine, b * ty + d, 0.f, 0.f, 1.f);
        _transformUpdated = true;
    }

    return _transform;
}
