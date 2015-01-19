#ifndef Ancona_Engine_Screen_AbstractScreen_H_
#define Ancona_Engine_Screen_AbstractScreen_H_

#include "ScreenManager.hpp"

namespace ild
{

/**
 * @brief  Base definition for a Screen
 *
 * @author Tucker Lein
 */
class AbstractScreen 
{
    public:
        /**
         * @brief Creates a new screen
         *
         * @param manager ScreenManager instance used by the game
         */
        AbstractScreen(ScreenManager & manager);

        /**
         * @brief Can be overridden to initialize the screen.  
         * Will be called just before Update is called for the
         * first time.
         */
        virtual void Init() { }

        /**
         * @brief Handles the update logic on the screen
         *
         * @param delta time since last update
         */
        virtual void Update(float delta) = 0;

        /**
         * @brief Handles the draw logic on the screen
         */
        virtual void Draw() = 0;
        
        /**
         * @brief Used by the ScreenManager to call the Init
         * function at the correct time.
         */
        bool __Initialized;

    protected:
        /**
         * @brief Manages all the screens in the game
         */
        ScreenManager & _manager;
};

}

#endif
