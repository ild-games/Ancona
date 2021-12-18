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
    static bool IsFingerPressed(int64_t finger);

    /**
     * @brief Deteremines if a finger was just released
     *
     * @param  finger which finger to determine if it was released
     *
     * @return true if the finger is released, otherwise false
     */
    static bool IsFingerReleased(int64_t finger);

    /**
     * @brief Deteremines if a finger is down
     *
     * @param  finger finger to check if it is down
     *
     * @return true if the finger is down, otherwise false
     */
    static bool IsFingerDown(int64_t finger);
    static ild::Vector2i FingerPosition(int64_t finger);

    /**
     * @brief INTERNAL ONLY
     *        Adds a finger press event for the given finger.
     *
     * @param finger finger being pressed
     */
    static void _AddFingerPress(int64_t finger, int x, int y);

    /**
     * @brief INTERNAL ONLY
     *        Adds a finger released event for the given finger.
     *
     * @param finger finger being released
     */
    static void _AddFingerRelease(int64_t finger);
    static void _AddFingerMoved(int64_t finger, int x, int y);

    /**
     * @brief INTERNAL ONLY
     *        Clears all finger events
     */
    static void _ClearFingers();
    static void _ClearAllFingersState();

  private:
    static std::set<int64_t> _pressedFingers;
    static std::set<int64_t> _releasedFingers;
    static std::set<int64_t> _heldFingers;
    static std::map<int64_t, unsigned long> _heldFingersToFrameCount;
    static std::set<int64_t> _heldFingersToClear;
    static std::map<int64_t, ild::Vector2i> _fingerPosition;
};

} // namespace ildhal

#endif
