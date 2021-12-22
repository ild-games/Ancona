// Altered SFML Transformable.cpp for Ancona's namespace

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

#include <Ancona/Graphics/Transform.hpp>

namespace ild
{

Transform::Transform() :
        _origin(0, 0),
        _position(0, 0),
        _rotation(0),
        _scale(1, 1),
        _transform(),
        _transformNeedUpdate(true),
        _inverseTransform(),
        _inverseTransformNeedUpdate(true)
{
}

void Transform::Move(float offsetX, float offsetY)
{
    position(_position.x + offsetX, _position.y + offsetY);
}

void Transform::Move(const Vector2f & offset)
{
    position(_position.x + offset.x, _position.y + offset.y);
}

void Transform::Rotate(float angle)
{
    rotation(_rotation + angle);
}

void Transform::Scale(float factorX, float factorY)
{
    scale(_scale.x * factorX, _scale.y * factorY);
}

void Transform::Scale(const Vector2f & factor)
{
    scale(_scale.x * factor.x, _scale.y * factor.y);
}

Transform & Transform::Combine(const Transform & combineWith)
{
    _origin += combineWith._origin;
    _position += combineWith._position;
    _rotation += combineWith._rotation;
    _scale += combineWith._scale;

    _transform = _transform.Combine(combineWith._transform);
    _inverseTransform = _inverseTransform.Combine(combineWith._inverseTransform);

    return *this;
}

/* getters and setters */

void Transform::position(float x, float y)
{
    _position.x = x;
    _position.y = y;
    _transformNeedUpdate = true;
    _inverseTransformNeedUpdate = true;
}

void Transform::position(const Vector2f & newPosition)
{
    position(newPosition.x, newPosition.y);
}

void Transform::rotation(float angle)
{
    _rotation = static_cast<float>(fmod(angle, 360));
    if (_rotation < 0)
    {
        _rotation += 360.f;
    }

    _transformNeedUpdate = true;
    _inverseTransformNeedUpdate = true;
}

void Transform::scale(float factorX, float factorY)
{
    _scale.x = factorX;
    _scale.y = factorY;
    _transformNeedUpdate = true;
    _inverseTransformNeedUpdate = true;
}

void Transform::scale(const Vector2f & factors)
{
    scale(factors.x, factors.y);
}

void Transform::origin(float x, float y)
{
    _origin.x = x;
    _origin.y = y;
    _transformNeedUpdate = true;
    _inverseTransformNeedUpdate = true;
}

void Transform::origin(const Vector2f & newOrigin)
{
    origin(newOrigin.x, newOrigin.y);
}

const Vector2f & Transform::position() const
{
    return _position;
}

float Transform::rotation() const
{
    return _rotation;
}

const Vector2f & Transform::scale() const
{
    return _scale;
}

const Vector2f & Transform::origin() const
{
    return _origin;
}

const MatrixTransform & Transform::transform() const
{
    // Recompute the combined transform if needed
    if (_transformNeedUpdate)
    {
        float angle = -_rotation * 3.141592654f / 180.f;
        float cosine = static_cast<float>(std::cos(angle));
        float sine = static_cast<float>(std::sin(angle));
        float sxc = _scale.x * cosine;
        float syc = _scale.y * cosine;
        float sxs = _scale.x * sine;
        float sys = _scale.y * sine;
        float tx = -_origin.x * sxc - _origin.y * sys + _position.x;
        float ty = _origin.x * sxs - _origin.y * syc + _position.y;

        _transform = MatrixTransform(sxc, sys, tx, -sxs, syc, ty, 0.f, 0.f, 1.f);
        _transformNeedUpdate = false;
    }

    return _transform;
}

const MatrixTransform & Transform::inverseTransform() const
{
    // Recompute the inverse transform if needed
    if (_inverseTransformNeedUpdate)
    {
        _inverseTransform = transform().Inverse();
        _inverseTransformNeedUpdate = false;
    }

    return _inverseTransform;
}

Transform operator*(const Transform & left, const Transform & right)
{
    Transform newTransform = left;
    newTransform._transform = left._transform * right._transform;
    return newTransform;
}

Transform & operator*=(Transform & left, const Transform & right)
{
    left._transform *= right._transform;
    return left;
}

Vector2f operator*(const Transform & left, const Vector2f & right)
{
    return left._transform.TransformPoint(right);
}

bool operator==(const Transform & left, const Transform & right)
{
    return left._transform == right._transform;
}

bool operator!=(const Transform & left, const Transform & right)
{
    return !(left._transform == right._transform);
}

} // namespace ild
