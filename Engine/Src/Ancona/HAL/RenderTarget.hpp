// Altered SFML RenderTarget.hpp for Ancona's HAL abstraction layer

////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
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

#ifndef Ancona_HAL_RenderTarget_H_
#define Ancona_HAL_RenderTarget_H_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

namespace ildhal
{

namespace priv
{
    class RenderTargetImpl;
}

class RenderTarget
{
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Clear the entire target with a single color
        ///
        /// This function is usually called once every frame,
        /// to clear the previous contents of the target.
        ///
        /// \param color Fill color to use to clear the render target
        ///
        ////////////////////////////////////////////////////////////
        void Clear(const sf::Color & color = sf::Color(0, 0, 0, 255));

        ////////////////////////////////////////////////////////////
        /// \brief Draw a drawable object to the render target
        ///
        /// \param drawable Object to draw
        /// \param states   Render states to use for drawing
        ///
        ////////////////////////////////////////////////////////////
        void Draw(const sf::Drawable & drawable, const sf::RenderStates & states = sf::RenderStates::Default);

        ////////////////////////////////////////////////////////////
        /// \brief Change the current active view
        ///
        /// The view is like a 2D camera, it controls which part of
        /// the 2D scene is visible, and how it is viewed in the
        /// render target.
        /// The new view will affect everything that is drawn, until
        /// another view is set.
        /// The render target keeps its own copy of the view object,
        /// so it is not necessary to keep the original one alive
        /// after calling this function.
        /// To restore the original view of the target, you can pass
        /// the result of getDefaultView() to this function.
        ///
        /// \param view New view to use
        ///
        /// \see getView, getDefaultView
        ///
        ////////////////////////////////////////////////////////////
        void SetView(const sf::View & view);

        ////////////////////////////////////////////////////////////
        /// \brief Get the default view of the render target
        ///
        /// The default view has the initial size of the render target,
        /// and never changes after the target has been created.
        ///
        /// \return The default view of the render target
        ///
        /// \see setView, getView
        ///
        ////////////////////////////////////////////////////////////
        const sf::View & GetDefaultView() const;

        ////////////////////////////////////////////////////////////
        /// \brief Convert a point from target coordinates to world
        ///        coordinates, using the current view
        ///
        /// This function is an overload of the mapPixelToCoords
        /// function that implicitly uses the current view.
        /// It is equivalent to:
        /// \code
        /// target.mapPixelToCoords(point, target.getView());
        /// \endcode
        ///
        /// \param point Pixel to convert
        ///
        /// \return The converted point, in "world" coordinates
        ///
        /// \see mapCoordsToPixel
        ///
        ////////////////////////////////////////////////////////////
        sf::Vector2f MapPixelToCoords(const sf::Vector2i& point, const sf::View & view) const;

        ////////////////////////////////////////////////////////////
        /// \brief Reset the internal OpenGL states so that the target is ready for drawing
        ///
        /// This function can be used when you mix SFML drawing
        /// and direct OpenGL rendering, if you choose not to use
        /// pushGLStates/popGLStates. It makes sure that all OpenGL
        /// states needed by SFML are set, so that subsequent draw()
        /// calls will work as expected.
        ///
        /// Example:
        /// \code
        /// // OpenGL code here...
        /// glPushAttrib(...);
        /// window.resetGLStates();
        /// window.draw(...);
        /// window.draw(...);
        /// glPopAttrib(...);
        /// // OpenGL code here...
        /// \endcode
        ///
        ////////////////////////////////////////////////////////////
        void ResetGLStates();

        ////////////////////////////////////////////////////////////
        /// \brief Return the size of the rendering region of the target
        ///
        /// \return Size in pixels
        ///
        ////////////////////////////////////////////////////////////
        virtual sf::Vector2u GetSize() const = 0;

        /* getters and setters */
        priv::RenderTargetImpl & getRenderTargetImpl() const { return *_pimpl; }
    protected:

        std::unique_ptr<priv::RenderTargetImpl> _pimpl;
};

}

#endif
