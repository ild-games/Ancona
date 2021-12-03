#ifndef Ancona_HAL_SFML_RenderTargetImpl_H_
#define Ancona_HAL_SFML_RenderTargetImpl_H_

#include <SFML/Graphics.hpp>

#include <Ancona/HAL/RenderTarget.hpp>

namespace ildhal
{

namespace priv
{

class RenderTargetImpl
{
  public:
    /* getters and setters */
    sf::RenderTarget &sfmlRenderTarget() const
    {
        return *_sfmlRenderTarget;
    }

  protected:
    std::unique_ptr<sf::RenderTarget> _sfmlRenderTarget;
};

} // namespace priv

} // namespace ildhal

#endif
