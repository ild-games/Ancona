// Altered SFML Music.hpp for Ancona's HAL abstraction layer

////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast MulMusicdia Library
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

#include <string>

#include <Ancona/HAL/SoundSource.hpp>
#include <Ancona/HAL/Time.hpp>

namespace ildhal
{

namespace priv
{
class MusicImpl;
}

class Music : public SoundSource
{
  public:
    Music();

    void Play() override;
    void Pause() override;
    void Stop() override;
    bool OpenFromFile(const std::string & filename);

    /* getters and setters */
    void loop(bool newLoop);
    void playingOffset(Time timeOffset);
    SoundSource::Status status() const override;
    void volume(float volume) override;
    priv::MusicImpl & musicImpl() const;
};

} // namespace ildhal
