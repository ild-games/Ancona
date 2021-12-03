// Altered SFML SoundSource.hpp for Ancona's HAL abstraction layer

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

#ifndef Ancona_HAL_SoundSource_H_
#define Ancona_HAL_SoundSource_H_

#include <memory>

namespace ildhal
{

namespace priv
{
    class SoundSourceImpl;
}

class SoundSource
{
    public:
        enum Status
        {
            Stopped, ///< Sound is not playing
            Paused,  ///< Sound is paused
            Playing  ///< Sound is playing
        };

        virtual void Play() = 0;
        virtual void Pause() = 0;
        virtual void Stop() = 0;

        /* getters and setters */
        Status status() const;
        void volume(float volume);

        priv::SoundSourceImpl & soundSourceImpl() const { return *_pimpl; }
    protected:

        std::unique_ptr<priv::SoundSourceImpl> _pimpl;
};

}


#endif
