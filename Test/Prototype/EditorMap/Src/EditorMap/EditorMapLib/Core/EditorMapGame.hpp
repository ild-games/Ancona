#ifndef EditorMap_Core_EditorMapGame_H_
#define EditorMap_Core_EditorMapGame_H_

#include <Ancona/Core2D/Core/Game.hpp>
#include "EditorMapPlatformFactory.hpp"

namespace ild
{

/**
 * @brief Game class for initial game setup.
 */
class EditorMapGame : public Game
{

    public:
        /**
         * @brief Constructs the game with the desired platform and screen size
         *
         * @param width Width of screen
         * @param height Height of screen
         * @param platform EditorMapPlatformFactory for the platform launched on
         */
        EditorMapGame(
                int width,
                int height,
                EditorMapPlatformFactory * platform);

    protected:
        /**
         * @brief Used to initialize the first screen of the game.
         */
        void CreateInitialScreen();

    private:
        EditorMapPlatformFactory * _platform;

};

}

#endif
