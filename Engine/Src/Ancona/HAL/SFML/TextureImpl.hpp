#ifndef Ancona_HAL_SFML_TextureImpl_H_
#define Ancona_HAL_SFML_TextureImpl_H_

#include <SFML/Graphics.hpp>

#include <Ancona/HAL/Texture.hpp>

namespace ildhal
{

namespace priv
{

class TextureImpl
{
  public:
    TextureImpl();
    ~TextureImpl();

    /* getters and setters */
    sf::Texture &sfmlTexture() const
    {
        return *_sfmlTexture;
    }

  private:
    sf::Texture *_sfmlTexture;
};

} // namespace priv

} // namespace ildhal

#endif
