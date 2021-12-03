// Altered SFML RenderStates.hpp for Ancona's namespace

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

#ifndef Ancona_HAL_RenderStates_H_
#define Ancona_HAL_RenderStates_H_

#include <memory>

#include <Ancona/Graphics/Transform.hpp>
#include <Ancona/HAL/BlendMode.hpp>

namespace ildhal
{

class Texture;

namespace priv
{
class RenderStatesImpl;
}

class RenderStates
{
  public:
    static const RenderStates Default;

    RenderStates();
    RenderStates(const BlendMode &blendMode);
    RenderStates(const ild::Transform &transform);
    RenderStates(const BlendMode &blendMode, const ild::Transform &transform, const Texture &texture);

    priv::RenderStatesImpl &renderStatesImpl() const
    {
        return *_pimpl;
    }

  private:
    std::unique_ptr<priv::RenderStatesImpl> _pimpl;
};

} // namespace ildhal

#endif
