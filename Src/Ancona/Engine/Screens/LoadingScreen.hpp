#ifndef Ancona_Engine_Screens_LoadingScreen_H_
#define Ancona_Engine_Screens_LoadingScreen_H_

#include <memory>

#include <Ancona/Engine/Loading/MapLoader.hpp>
#include <Ancona/Engine/Resource/RequestList.hpp>
#include <Ancona/Engine/Screens/AbstractScreen.hpp>

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
         * @param screenLoading The Screen the the loading screen is loading.
         * @param manager ScreenManager instance for the game.
         */
        LoadingScreen(
                AbstractScreen * screenLoading,
                ScreenManager & manager);

        /**
         * @brief Loads in the next resource.
         *
         * @param delta Seconds since last update.
         */
        void Update(float delta);

        /**
         * @brief Draws the default loading bar.
         */
        virtual void Draw(float delta);

        /**
         * @brief Used to determine if the screen is still in a state of entering.
         */
        virtual void Entering(float delta);

        /**
         * @brief Used to determine if the screen is still in a state of exiting.
         */
        virtual void Exiting(float delta);

        /* getters and setters */
        ScreenSystemsContainer * systemsContainer() override;
    private:
        /**
         * @brief The Screen that will be loaded.
         */
        AbstractScreen * _screenLoading;
        /**
         * @brief Loads in the map data.
         */
        std::unique_ptr<MapLoader> _mapLoader;
        /**
         * @brief Systems container for the load screen.
         */
        std::unique_ptr<ScreenSystemsContainer> _systemsContainer;

};

}

#endif
