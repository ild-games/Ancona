#ifndef Ancona_HAL_SFML_RenderStatesImpl_H_
#define Ancona_HAL_SFML_RenderStatesImpl_H_

#include <SFML/Graphics.hpp>

#include <Ancona/HAL/RenderStates.hpp>

namespace ildhal
{

namespace priv
{

class RenderStatesImpl
{
  public:
    RenderStatesImpl(const sf::BlendMode &blendMode, const sf::Transform &transform, const sf::Texture *texture);

    /* getters and setters */
    sf::RenderStates &sfmlRenderStates() const
    {
        return *_sfmlRenderStates;
    }

  protected:
    std::unique_ptr<sf::RenderStates> _sfmlRenderStates;
};

} // namespace priv

} // namespace ildhal

#endif
