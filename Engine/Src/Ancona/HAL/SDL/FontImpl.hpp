#pragma once

#include <SFML/Graphics.hpp>

#include <Ancona/HAL/Font.hpp>

namespace ildhal
{

namespace priv
{

class FontImpl
{
  public:
    FontImpl();

    /* getters and setters */
    sf::Font & sfmlFont() const { return *_sfmlFont; }

  private:
    std::unique_ptr<sf::Font> _sfmlFont;
};

} // namespace priv

} // namespace ildhal
