#include <string>

#include <SDL2/SDL.h>

#include <Ancona/HAL/SDL/RapidJsonOStreamWrapperImpl.hpp>
#include <Ancona/System/Log.hpp>
#include <Ancona/Util/Assert.hpp>

namespace ildhal
{

/* Pimpl Implementation */
bool priv::RapidJsonOStreamWrapperImpl::LoadFromFile(const std::string & filename)
{
    SDL_RWops * rwops = SDL_RWFromFile(filename.c_str(), "wb");
    if (rwops == nullptr)
    {
        return false;
    }

    _sdlRwops = rwops;
    return true;
}

/* HAL Interface Implementation */
RapidJsonOStreamWrapper::RapidJsonOStreamWrapper()
  : _pimpl(std::make_unique<priv::RapidJsonOStreamWrapperImpl>())
{
}

bool RapidJsonOStreamWrapper::LoadFromFile(const std::string & filename)
{
    return rapidJsonStreamWrapperImpl().LoadFromFile(filename);
}

char RapidJsonOStreamWrapper::Peek() const
{
    ILD_Assert(false, "Peek not implemented in RapidJsonOStreamWrapper");
    SDL_RWops * rwops = &rapidJsonStreamWrapperImpl().sdlRwops();

    char peekedChar;
    auto numObjectsRead = SDL_RWread(rwops, &peekedChar, sizeof(char), 1);
    if (numObjectsRead == 0) {
      return '\0';
    }
    SDL_RWseek(rwops, -sizeof(char), RW_SEEK_CUR);

    return peekedChar;
}

char RapidJsonOStreamWrapper::Take()
{
    ILD_Assert(false, "Take not implemented in RapidJsonOStreamWrapper");
    SDL_RWops * rwops = &rapidJsonStreamWrapperImpl().sdlRwops();

    char peekedChar;
    auto numObjectsRead = SDL_RWread(rwops, &peekedChar, sizeof(char), 1);
    if (numObjectsRead == 0) {
      return '\0';
    }

    return peekedChar;
}

size_t RapidJsonOStreamWrapper::Tell()
{
    ILD_Assert(false, "Tell not implemented in RapidJsonOStreamWrapper");
    SDL_RWops * rwops = &rapidJsonStreamWrapperImpl().sdlRwops();

    return SDL_RWtell(rwops);
}

char * RapidJsonOStreamWrapper::PutBegin()
{
    ILD_Assert(false, "PutBegin not implemented in RapidJsonOStreamWrapper");
    return nullptr;
}

void RapidJsonOStreamWrapper::Put(char c)
{
    SDL_RWops * rwops = &rapidJsonStreamWrapperImpl().sdlRwops();

    SDL_RWwrite(rwops, &c, sizeof(c), 1);
}

void RapidJsonOStreamWrapper::Flush()
{
    SDL_RWops * rwops = &rapidJsonStreamWrapperImpl().sdlRwops();

    SDL_RWclose(rwops);
}

size_t RapidJsonOStreamWrapper::PutEnd(char* begin)
{
    ILD_Assert(false, "PutEnd not implemented in RapidJsonOStreamWrapper");
}

} // namespace ildhal
