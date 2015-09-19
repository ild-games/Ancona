#ifndef Rotation_Core_RotationGame_H_
#define Rotation_Core_RotationGame_H_

#include <Ancona/Core2D/Core/Game.hpp>
#include "RotationPlatformFactory.hpp"

namespace ild
{

/**
 * @brief Game class for initial game setup.
 */
class RotationGame : public Game
{

    public:
        /**
         * @brief Constructs the game with the desired platform and screen size
         *
         * @param width Width of screen
         * @param height Height of screen
         * @param platform RotationPlatformFactory for the platform launched on
         */
        RotationGame(
                int width,
                int height,
                RotationPlatformFactory * platform);

    protected:
        /**
         * @brief Used to initialize the first screen of the game.
         */
        void CreateInitialScreen();

    private:
        RotationPlatformFactory * _platform;

};

}

#endif
