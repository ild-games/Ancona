#ifndef Ancona_Engine_InputDevices_Mouse_H_
#define Ancona_Engine_InputDevices_Mouse_H_

#include <SFML/Window.hpp>
#include <unordered_map>
#include <set>

namespace ild
{

/**
 * @brief Provides static methods to determine the state of the mouse.
 */
class Mouse
{
    public:
        /**
         * @brief Deteremines if a button was just pressed
         *
         * @param  btn sf::Mouse::Button to check if it is pressed
         *
         * @return true if the button is pressed, otherwise false
         */
        static bool IsButtonPressed(const sf::Mouse::Button & btn);

        /**
         * @brief Deteremines if a button was just released
         *
         * @param  btn sf::Mouse::Button to check if it is released
         *
         * @return true if the button is released, otherwise false
         */
        static bool IsButtonReleased(const sf::Mouse::Button & btn);

        /**
         * @brief Deteremines if a button is down
         *
         * @param  btn sf::Mouse::Button to check if it is down
         *
         * @return true if the button is down, otherwise false
         */
        static bool IsButtonDown(const sf::Mouse::Button & btn);

        /**
         * @brief INTERNAL ONLY
         *        Adds a button press event for the given button
         *
         * @param btn sf::Mouse::Button being pressed
         */
        static void _AddButtonPress(const sf::Mouse::Button & btn);

        /**
         * @brief INTERNAL ONLY
         *        Adds a button released event for the given button
         *
         * @param btn sf::Mouse::Button being released
         */
        static void _AddButtonRelease(const sf::Mouse::Button & btn);

        /**
         * @brief INTERNAL ONLY
         *        Clears all button events
         */
        static void _ClearButtons();

    private:
        static std::set<sf::Mouse::Button> _pressedButtons;
        static std::set<sf::Mouse::Button> _releasedButtons;
};

}

#endif
