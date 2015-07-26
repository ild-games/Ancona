#ifndef Ghosted_Core_GhostedGame_H_
#define Ghosted_Core_GhostedGame_H_

#include <Ancona/Core2D/Core/Game.hpp>
#include "GhostedPlatformFactory.hpp"

namespace ild
{

/**
 * @brief Game class for initial game setup.
 */
class GhostedGame : public Game
{

    public:
        /**
         * @brief Constructs the game with the desired platform and screen size
         *
         * @param width Width of screen
         * @param height Height of screen
         * @param platform GhostedPlatformFactory for the platform launched on
         */
        GhostedGame(
                int width,
                int height,
                GhostedPlatformFactory * platform);

    protected:
        /**
         * @brief Used to initialize the first screen of the game.
         */
        void CreateInitialScreen();

    private:
        GhostedPlatformFactory * _platform;

};

}

#endif
