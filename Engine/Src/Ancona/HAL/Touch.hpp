#ifndef Ancona_HAL_Touch_H_
#define Ancona_HAL_Touch_H_

#include <map>
#include <set>
#include <unordered_map>

#include <Ancona/Util/Vector2.hpp>

namespace ildhal
{

/**
 * @brief Provides static methods to determine the state of the touch input for mobile
 */
class Touch
{
    public:
        /**
         * @brief Deteremines if a finger was just pressed
         *
         * @param  finger which finger to determine if it was pressed
         *
         * @return true if the finger is pressed, otherwise false
         */
        static bool IsFingerPressed(unsigned int finger);

        /**
         * @brief Deteremines if a finger was just released
         *
         * @param  finger which finger to determine if it was released
         *
         * @return true if the finger is released, otherwise false
         */
        static bool IsFingerReleased(unsigned int finger);

        /**
         * @brief Deteremines if a finger is down
         *
         * @param  finger finger to check if it is down
         *
         * @return true if the finger is down, otherwise false
         */
        static bool IsFingerDown(unsigned int finger);
        static ild::Vector2i FingerPosition(unsigned int finger);

        /**
         * @brief INTERNAL ONLY
         *        Adds a finger press event for the given finger.
         *
         * @param finger finger being pressed
         */
        static void _AddFingerPress(unsigned int finger, int x, int y);

        /**
         * @brief INTERNAL ONLY
         *        Adds a finger released event for the given finger.
         *
         * @param finger finger being released
         */
        static void _AddFingerRelease(unsigned int finger);
        static void _AddFingerMoved(unsigned int finger, int x, int y);

        /**
         * @brief INTERNAL ONLY
         *        Clears all finger events
         */
        static void _ClearFingers();
        static void _ClearAllFingersState();

    private:
        static std::set<unsigned int> _pressedFingers;
        static std::set<unsigned int> _releasedFingers;
        static std::set<unsigned int> _heldFingers;
        static std::map<unsigned int, unsigned int> _heldFingersToFrameCount;
        static std::set<unsigned int> _heldFingersToClear;
        static std::map<unsigned int, ild::Vector2i> _fingerPosition;
};

}

#endif
