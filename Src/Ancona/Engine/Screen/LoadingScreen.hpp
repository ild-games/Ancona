#ifndef Ancona_Engine_Screen_LoadingScreen_H_
#define Ancona_Engine_Screen_LoadingScreen_H_

#include <Ancona/Engine/Resource/RequestList.hpp>
#include <Ancona/Engine/Screen/AbstractScreen.hpp>

namespace ild
{

/**
 * @brief  Screen used when loading in resources.
 *
 * @author Tucker Lein
 */
class LoadingScreen : public AbstractScreen
{
    public:
        /**
         * @brief Creates the loading screen.
         *
         * @param manager ScreenManager instance for the game.
         * @param requestList RequestList the screen is loading
         */
        LoadingScreen(ScreenManager & manager, RequestList & requestList);

        /**
         * @brief Loads in the next resource.
         *
         * @param delta Seconds since last update.
         */
        void Update(float delta);

        /**
         * @brief Draws the default loading bar.
         */
        virtual void Draw();

    private:
        /**
         * @brief The request list that is loading during the loading screen.
         */
        RequestList & _requestList;
};

}

#endif
