#ifndef Ancona_HAL_SFML_RenderTextureImpl_H_
#define Ancona_HAL_SFML_RenderTextureImpl_H_

#include <SFML/Graphics.hpp>

#include <Ancona/HAL/RenderTexture.hpp>
#include <Ancona/HAL/SFML/RenderTargetImpl.hpp>

namespace ildhal
{

namespace priv
{

class RenderTextureImpl : public RenderTargetImpl
{
  public:
    RenderTextureImpl();

    /* getters and setters */
    sf::RenderTexture &sfmlRenderTexture() const;
};

} // namespace priv

} // namespace ildhal

#endif
