#ifndef Ancona_Engine_InputDevices_Mouse_H_
#define Ancona_Engine_InputDevices_Mouse_H_

#include <SFML/Window.hpp>
#include <unordered_map>
#include <set>

namespace ild
{

class Mouse
{
    public:
        static bool IsButtonPressed(const sf::Mouse::Button & btn);
        static bool IsButtonReleased(const sf::Mouse::Button & btn);
        static bool IsButtonDown(const sf::Mouse::Button & btn);
        static void _AddButtonPress(const sf::Mouse::Button & btn);
        static void _AddButtonRelease(const sf::Mouse::Button & btn);
        static void _ClearButtons();

    private:
        static std::set<sf::Mouse::Button> _pressedButtons;

        static std::set<sf::Mouse::Button> _releasedButtons;
};

}

#endif
