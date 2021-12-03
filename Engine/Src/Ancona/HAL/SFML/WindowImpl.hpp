#ifndef Ancona_HAL_SFML_WindowImpl_H_
#define Ancona_HAL_SFML_WindowImpl_H_

#include <SFML/Graphics.hpp>

#include <Ancona/HAL/Event.hpp>
#include <Ancona/HAL/SFML/RenderTargetImpl.hpp>
#include <Ancona/HAL/Window.hpp>

namespace ildhal
{

namespace priv
{

class WindowImpl : public RenderTargetImpl
{
  public:
    WindowImpl(const std::string &title, int width, int height, unsigned int style = WindowStyle::Default);

    /* getters and setters */
    sf::RenderWindow &sfmlRenderWindow() const;
};

} // namespace priv

} // namespace ildhal

#endif
