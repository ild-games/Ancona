#pragma once

#include <string>

#include <Ancona/HAL/SDL/DrawableImpl.hpp>
#include <Ancona/HAL/Text.hpp>

namespace ildhal
{

namespace priv
{

class TextImpl : public DrawableImpl
{
  public:
    /* getters and setters */
    const std::string & text() const { return _text; }

  private:
    std::string _text = "1";
};

} // namespace priv

} // namespace ildhal
