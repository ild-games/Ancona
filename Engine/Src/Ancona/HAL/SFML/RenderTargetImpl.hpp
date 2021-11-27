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
        RenderTargetImpl(std::unique_ptr<sf::RenderTarget> sfmlRenderTarget);

        /* getters and setters */
        sf::RenderTarget & getSfmlRenderTarget() const { return *_sfmlRenderTarget; }

    protected:
        std::unique_ptr<sf::RenderTarget> _sfmlRenderTarget;
};

}

}

#endif
