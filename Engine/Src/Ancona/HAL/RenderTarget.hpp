// Altered SFML RenderTarget.hpp for Ancona's HAL abstraction layer

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

#include <Ancona/Graphics/Color.hpp>
#include <Ancona/Graphics/View.hpp>
#include <Ancona/HAL/Drawable.hpp>
#include <Ancona/HAL/RenderStates.hpp>
#include <Ancona/Util/Vector2.hpp>

namespace ildhal
{

namespace priv
{
class RenderTargetImpl;
}

class RenderTarget
{
  public:
    void Clear(const ild::Color & color = ild::Color(0, 0, 0, 255));
    void Draw(const Drawable & drawable, const RenderStates & states = RenderStates::Default);
    ild::Vector2f MapPixelToCoords(const ild::Vector2i & point, const ild::View & view) const;
    void ResetGLStates();

    /* getters and setters */
    const ild::View defaultView() const;
    void view(const ild::View & view);
    virtual ild::Vector2u size() const = 0;

    priv::RenderTargetImpl & renderTargetImpl() const { return *_pimpl; }

  protected:
    std::unique_ptr<priv::RenderTargetImpl> _pimpl;
};

} // namespace ildhal
