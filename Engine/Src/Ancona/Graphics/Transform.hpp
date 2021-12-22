// Altered SFML Transformable.hpp for Ancona's namespace

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

#include <Ancona/Graphics/MatrixTransform.hpp>
#include <Ancona/Util/Vector2.hpp>

namespace ild
{

class Transform
{
  public:
    Transform();

    void Move(float offsetX, float offsetY);
    void Move(const Vector2f & offset);
    void Rotate(float angle);
    void Scale(float factorX, float factorY);
    void Scale(const Vector2f & factor);
    Transform & Combine(const Transform & combineWith);

    /* getters and setters */
    void position(float x, float y);
    void position(const Vector2f & newPosition);
    void rotation(float angle);
    void scale(const Vector2f & factors);
    void scale(float x, float y);
    void origin(float x, float y);
    void origin(const Vector2f & newOrigin);
    const Vector2f & position() const;
    float rotation() const;
    const Vector2f & scale() const;
    const Vector2f & origin() const;
    const MatrixTransform & transform() const;
    const MatrixTransform & inverseTransform() const;

  private:
    friend Transform operator*(const Transform & left, const Transform & right);
    friend Transform & operator*=(Transform & left, const Transform & right);
    friend Vector2f operator*(const Transform & left, const Vector2f & right);
    friend bool operator==(const Transform & left, const Transform & right);
    friend bool operator!=(const Transform & left, const Transform & right);

    Vector2f _origin; ///< Origin of translation/rotation/scaling of the object
    Vector2f _position; ///< Position of the object in the 2D world
    float _rotation; ///< Orientation of the object, in degrees
    Vector2f _scale; ///< Scale of the object
    mutable MatrixTransform _transform; ///< Combined transformation of the object
    mutable bool _transformNeedUpdate; ///< Does the transform need to be recomputed?
    mutable MatrixTransform _inverseTransform; ///< Combined transformation of the object
    mutable bool _inverseTransformNeedUpdate; ///< Does the transform need to be recomputed?
};

Transform operator*(const Transform & left, const Transform & right);
Transform & operator*=(Transform & left, const Transform & right);
Vector2f operator*(const Transform & left, const Vector2f & right);
bool operator==(const Transform & left, const Transform & right);
bool operator!=(const Transform & left, const Transform & right);

} // namespace ild
