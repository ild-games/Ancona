#ifndef Ancona_Engine_InputDevices_Keyboard_H_
#define Ancona_Engine_InputDevices_Keyboard_H_

#include <SFML/Window.hpp>
#include <unordered_map>
#include <set>

namespace ild
{

/**
 * @brief Provides static methods to determine the state of the
 *        keyboard.
 *
 * @owner Tucker Lein
 */
class Keyboard
{
    public:
        /**
         * @brief Determines if a key was just pressed
         *
         * @param sf::Keyboard::Key key Key to check
         *
         * @return true if just pressed, otherwise false
         */
        static bool IsKeyPressed(const sf::Keyboard::Key & key);

        /**
         * @brief Determines if a key was just released
         *
         * @param sf::Keyboard::Key key Key to check
         *
         * @return true if just released, otherwise false
         */
        static bool IsKeyReleased(const sf::Keyboard::Key & key);

        /**
         * @brief Determines if a key is currently being held
         *        down
         *
         * @param sf::Keyboard::Key key Key to check
         *
         * @return true if being held down, otherwise false
         */
        static bool IsKeyDown(const sf::Keyboard::Key & key);

        /**
         * @brief Adds a key press into the manager. Only to be
         *        called by the game's event loop.
         *
         * @param sf::Keyboard::Key key Key that was just pressed
         */
        static void _AddKeyPress(const sf::Keyboard::Key & key);

        /**
         * @brief Adds a key release into the manager. Only to be
         *        called by the game's event loop.
         *
         * @param sf::Keyboard::Key key Key that was just 
         *        released
         */
        static void _AddKeyRelease(const sf::Keyboard::Key & key);

        /**
         * @brief Clears the status of the pressed and released
         *        keys. Only to be called by the game's event 
         *        loop.
         */
        static void _ClearKeys();
    private:

        /**
         * @brief Contains the keys that were just pressed
         */
        static std::set<sf::Keyboard::Key> _pressedKeys;

        /**
         * @brief Contains the keys that are were just released
         */
        static std::set<sf::Keyboard::Key> _releasedKeys;
};

}

#endif
