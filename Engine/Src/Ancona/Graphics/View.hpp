// Altered SFML View.hpp for Ancona's namespace

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

#ifndef Ancona_Graphics_View_H_
#define Ancona_Graphics_View_H_

#include <Ancona/Graphics/Rect.hpp>
#include <Ancona/Graphics/Transform.hpp>
#include <Ancona/Util/Vector2.hpp>

namespace ild
{

class View
{
    public:

        View();
        explicit View(const FloatRect& rectangle);

        View(const Vector2f& center, const Vector2f& size);
        void Reset(const FloatRect& rectangle);
        void Move(float offsetX, float offsetY);
        void Move(const Vector2f& offset);
        void Rotate(float angle);
        void Zoom(float factor);
        const Transform& InverseTransform() const;

        /* getters and setters */
        const Vector2f& center() const { return _center; }
        void center(float x, float y);
        void center(const Vector2f& centerPoint);

        const Vector2f& size() const { return _size; }
        void size(float width, float height);
        void size(const Vector2f& newSize);

        float rotation() const { return _rotation; }
        void rotation(float angle);

        const FloatRect& viewport() const { return _viewport; }
        void viewport(const FloatRect& viewport) { _viewport = viewport; }

        const Transform& transform() const;

    private:

        Vector2f          _center;              ///< Center of the view, in scene coordinates
        Vector2f          _size;                ///< Size of the view, in scene coordinates
        float             _rotation;            ///< Angle of rotation of the view rectangle, in degrees
        FloatRect         _viewport;            ///< Viewport rectangle, expressed as a factor of the render-target's size
        mutable Transform _transform;           ///< Precomputed projection transform corresponding to the view
        mutable Transform _inverseTransform;    ///< Precomputed inverse projection transform corresponding to the view
        mutable bool      _transformUpdated;    ///< Internal state telling if the transform needs to be updated
        mutable bool      _invTransformUpdated; ///< Internal state telling if the inverse transform needs to be updated
};

}


#endif
