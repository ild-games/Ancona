#ifndef Anona_Menu_Input_MenuTouch_H_
#define Anona_Menu_Input_MenuTouch_H_

#include <Ancona/Menu/Screens/MenuInputHandler.hpp>
#include <Ancona/Util/Vector2.hpp>

namespace ild
{

/**
 * @brief Touch input handler for the menu.
 */
class MenuTouch: public MenuInputHandler
{
    public:
        /**
         * @brief Captures input and calls out to the inputComponent's actions.
         */
        virtual void HandleInput(float delta) override;
        virtual bool IsAnyFingerDown() override;

    private:
        ild::Vector2f _lastPosition;
        void HandleFingerPress(const int finger, float delta);
};

}

#endif
