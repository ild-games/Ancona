#ifndef Ancona_Game_Screens_TestScreen_H_
#define Ancona_Game_Screens_TestScreen_H_

namespace ild
{

/**
 * @brief Screen used for various testing 
 *
 * @author Tucker Lein
 */
class TestScreen : public AbstractScreen
{
    public:
        /**
         * @brief Creates the test screen
         *
         * @param manager ScreenManager instance of the game
         * @param requestList RequestList the screen is loading
         */
        TestScreen(
                ScreenManager & manager,
                RequestList & requestList);

        void Update(float delta);

    private:
};

}

#endif
