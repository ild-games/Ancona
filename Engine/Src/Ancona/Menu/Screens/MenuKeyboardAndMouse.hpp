#ifndef Anona_Menu_Input_MenuKeyboardAndMouse_H_
#define Anona_Menu_Input_MenuKeyboardAndMouse_H_

#include "MenuInputHandler.hpp"

namespace ildmenu
{

/**
 * @brief Keyboard & mouse handler for the menu.
 */
class MenuKeyboardAndMouse: public MenuInputHandler
{
    public:
        /**
         * @brief Captures input and calls out to the inputComponent's actions.
         */
        virtual void HandleInput(float delta) override;
};

}

#endif
