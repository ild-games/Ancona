#ifndef Ancona_Engine_InputDevices_Joystick_H_
#define Ancona_Engine_InputDevices_Joystick_H_

#include <SFML/Window.hpp>
#include <unordered_map>
#include <set>

namespace ild
{

class Joystick
{
    public:
        static bool IsButtonPressed(const int joystick, const int button);
        static bool IsButtonReleased(const int joystick, const int button);
        static bool IsButtonDown(const int joystick, const int button);
        static void _AddButtonPress(const int joystick, const int button);
        static void _AddButtonRelease(const int joystick, const int button);
        static void _ClearButtons();
    private:

        static std::unordered_map<int, std::set<int>> _pressedButtons;
        static std::unordered_map<int, std::set<int>> _releasedButtons;
};

}

#endif
