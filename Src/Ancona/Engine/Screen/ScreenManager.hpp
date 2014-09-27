#ifndef Ancona_Engine_Screen_ScreenManager_H_
#define Ancona_Engine_Screen_ScreenManager_H_

#include <stack>

namespace ild
{

class AbstractScreen;

/**
 * @brief  Responsible for managing all the screens that are loaded into the system.
 *         Screen are stored using stock logic, with the stack order being the order
 *         the screen were added to the system. This means the screen at the top of the stack
 *         is the current screen being run by the game, but when that screen exits it
 *         gets popped off the stack and the screen below it is then the active screen.
 *
 * @author Tucker Lein
 */
class ScreenManager 
{
    public:
        /**
         * @brief Pushs a new screen onto the manager
         *
         * @param screen Screen to push
         */
        void Push(AbstractScreen * screen);


        /**
         * @brief Pops the current screen off the manager. This removes the reference
         * to the screen and deletes the pointer.
         */
        void Pop();

        /**
         * @brief Updates the current screen
         *
         * @param delta time since last update
         */
        void Update(float delta);

        /**
         * @brief Renders the current screen
         */
        void Render();

    private:
        /**
         * @brief The current screens being managed, in the order they were added
         */
        std::stack<AbstractScreen *> _screens;
}

}

#endif
