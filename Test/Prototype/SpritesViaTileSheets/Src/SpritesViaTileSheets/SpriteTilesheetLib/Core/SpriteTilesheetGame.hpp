#ifndef SpriteTilesheet_Core_SpriteTilesheetGame_H_
#define SpriteTilesheet_Core_SpriteTilesheetGame_H_

#include <Ancona/Core2D/Core/Game.hpp>
#include "PlatformBase.hpp"

namespace ild
{

/**
 * @brief Game class for initial game setup.
 */
class SpriteTilesheetGame : public Game
{

    public:
        /**
         * @brief Constructs the game with the desired platform and screen size
         *
         * @param width Width of screen
         * @param height Height of screen
         * @param platform PlatformBase for the platform launched on
         */
        SpriteTilesheetGame(
                int width,
                int height,
                PlatformBase * platform);

    protected:
        /**
         * @brief Used to initialize the first screen of the game.
         */
        void CreateInitialScreen();

    private:
        PlatformBase * _platform;

};

}

#endif
