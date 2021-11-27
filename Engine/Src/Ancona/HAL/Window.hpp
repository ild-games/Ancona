// Altered SFML RenderWindow.hpp, Window.hpp, and WindowStyle.hpp for Ancona's HAL abstraction layer

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

#ifndef Ancona_HAL_Window_H_
#define Ancona_HAL_Window_H_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <Ancona/HAL/Event.hpp>
#include <Ancona/HAL/RenderTarget.hpp>

namespace ildhal
{

namespace WindowStyle
{
    ////////////////////////////////////////////////////////////
    /// \brief Enumeration of the window styles
    ///
    ////////////////////////////////////////////////////////////
    enum
    {
        None       = 0,      ///< No border / title bar (this flag and all others are mutually exclusive)
        Titlebar   = 1 << 0, ///< Title bar + fixed border
        Resize     = 1 << 1, ///< Title bar + resizable border + maximize button
        Close      = 1 << 2, ///< Title bar + close button
        Fullscreen = 1 << 3, ///< Fullscreen mode (this flag and all others are mutually exclusive)

        Default = Titlebar | Resize | Close ///< Default window style
    };
}

namespace priv
{
    class WindowImpl;
}

class Window : public RenderTarget
{
    public:

        Window(
            const std::string& title,
            int width,
            int height,
            unsigned int style = WindowStyle::Default);

        ~Window();

        ////////////////////////////////////////////////////////////
        /// \brief Limit the framerate to a maximum fixed frequency
        ///
        /// If a limit is set, the window will use a small delay after
        /// each call to display() to ensure that the current frame
        /// lasted long enough to match the framerate limit.
        /// SFML will try to match the given limit as much as it can,
        /// but since it internally uses sleep, whose precision
        /// depends on the underlying OS, the results may be a little
        /// unprecise as well (for example, you can get 65 FPS when
        /// requesting 60).
        ///
        /// \param limit Framerate limit, in frames per seconds (use 0 to disable limit)
        ///
        ////////////////////////////////////////////////////////////
        void SetFramerateLimit(unsigned int limit);

        ////////////////////////////////////////////////////////////
        /// \brief Enable or disable vertical synchronization
        ///
        /// Activating vertical synchronization will limit the number
        /// of frames displayed to the refresh rate of the monitor.
        /// This can avoid some visual artifacts, and limit the framerate
        /// to a good value (but not constant across different computers).
        ///
        /// Vertical synchronization is disabled by default.
        ///
        /// \param enabled True to enable v-sync, false to deactivate it
        ///
        ////////////////////////////////////////////////////////////
        void SetVerticalSyncEnabled(bool enabled);

        ////////////////////////////////////////////////////////////
        /// \brief Enable or disable automatic key-repeat
        ///
        /// If key repeat is enabled, you will receive repeated
        /// KeyPressed events while keeping a key pressed. If it is disabled,
        /// you will only get a single event when the key is pressed.
        ///
        /// Key repeat is enabled by default.
        ///
        /// \param enabled True to enable, false to disable
        ///
        ////////////////////////////////////////////////////////////
        void SetKeyRepeatEnabled(bool enabled);

        ////////////////////////////////////////////////////////////
        /// \brief Tell whether or not the window is open
        ///
        /// This function returns whether or not the window exists.
        /// Note that a hidden window (setVisible(false)) is open
        /// (therefore this function would return true).
        ///
        /// \return True if the window is open, false if it has been closed
        ///
        ////////////////////////////////////////////////////////////
        bool IsOpen() const;

        ////////////////////////////////////////////////////////////
        /// \brief Pop the event on top of the event queue, if any, and return it
        ///
        /// This function is not blocking: if there's no pending event then
        /// it will return false and leave \a event unmodified.
        /// Note that more than one event may be present in the event queue,
        /// thus you should always call this function in a loop
        /// to make sure that you process every pending event.
        /// \code
        /// Event event;
        /// while (window.pollEvent(event))
        /// {
        ///    // process event...
        /// }
        /// \endcode
        ///
        /// \param event Event to be returned
        ///
        /// \return True if an event was returned, or false if the event queue was empty
        ///
        /// \see waitEvent
        ///
        ////////////////////////////////////////////////////////////
        bool PollEvent(Event & event);

        ////////////////////////////////////////////////////////////
        /// \brief Display on screen what has been rendered to the window so far
        ///
        /// This function is typically called after all OpenGL rendering
        /// has been done for the current frame, in order to show
        /// it on screen.
        ///
        ////////////////////////////////////////////////////////////
        void Display();

        ////////////////////////////////////////////////////////////
        /// \brief Close the window and destroy all the attached resources
        ///
        /// After calling this function, the Window instance remains
        /// valid and you can call create() to recreate the window.
        /// All other functions such as pollEvent() or display() will
        /// still work (i.e. you don't have to test isOpen() every time),
        /// and will have no effect on closed windows.
        ///
        ////////////////////////////////////////////////////////////
        void Close();

        ////////////////////////////////////////////////////////////
        /// \brief Activate or deactivate the window as the current target
        ///        for OpenGL rendering
        ///
        /// A window is active only on the current thread, if you want to
        /// make it active on another thread you have to deactivate it
        /// on the previous thread first if it was active.
        /// Only one window can be active on a thread at a time, thus
        /// the window previously active (if any) automatically gets deactivated.
        /// This is not to be confused with requestFocus().
        ///
        /// \param active True to activate, false to deactivate
        ///
        /// \return True if operation was successful, false otherwise
        ///
        ////////////////////////////////////////////////////////////
        bool SetActive(bool active = true) const;

        ////////////////////////////////////////////////////////////
        /// \brief Change the title of the window
        ///
        /// \param title New title
        ///
        /// \see setIcon
        ///
        ////////////////////////////////////////////////////////////
        void SetTitle(const std::string & title);

        ////////////////////////////////////////////////////////////
        /// \brief Get the size of the rendering region of the window
        ///
        /// The size doesn't include the titlebar and borders
        /// of the window.
        ///
        /// \return Size in pixels
        ///
        ////////////////////////////////////////////////////////////
        virtual ild::Vector2u GetSize() const;

        // TODO remove when drawing HAL abstraction is finished, not needed at that time
        sf::RenderTarget & GetRenderTarget();

        /* getters and setters */
        priv::WindowImpl & getWindowImpl() const;
};

}

#endif
