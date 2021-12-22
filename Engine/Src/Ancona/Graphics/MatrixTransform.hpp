// Altered SFML Transform.hpp for Ancona's namespace

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
#include <Ancona/Util/Vector2.hpp>

namespace ild
{

class MatrixTransform
{
  public:
    MatrixTransform();
    MatrixTransform(float a00, float a01, float a02, float a10, float a11, float a12, float a20, float a21, float a22);

    Vector2f TransformPoint(float x, float y) const;
    Vector2f TransformPoint(const Vector2f & point) const;
    FloatRect TransformRect(const FloatRect & rectangle) const;
    MatrixTransform & Combine(const MatrixTransform & transform);
    MatrixTransform & Translate(float x, float y);
    MatrixTransform & Translate(const Vector2f & offset);
    MatrixTransform & Rotate(float angle);
    MatrixTransform & Rotate(float angle, float centerX, float centerY);
    MatrixTransform & Rotate(float angle, const Vector2f & center);
    MatrixTransform & Scale(float scaleX, float scaleY);
    MatrixTransform & Scale(float scaleX, float scaleY, float centerX, float centerY);
    MatrixTransform & Scale(const Vector2f & factors);
    MatrixTransform & Scale(const Vector2f & factors, const Vector2f & center);
    MatrixTransform Inverse() const;

    static const MatrixTransform Identity; ///< The identity transform (does nothing)

    /* getters and setters */
    const float * matrix() const;

  private:
    float _matrix[16]; ///< 4x4 matrix defining the transformation
};

MatrixTransform operator*(const MatrixTransform & left, const MatrixTransform & right);
MatrixTransform & operator*=(MatrixTransform & left, const MatrixTransform & right);
Vector2f operator*(const MatrixTransform & left, const Vector2f & right);
bool operator==(const MatrixTransform & left, const MatrixTransform & right);
bool operator!=(const MatrixTransform & left, const MatrixTransform & right);

} // namespace ild
