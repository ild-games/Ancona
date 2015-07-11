#ifndef SpriteTilesheet_Screens_TestScreen_H_
#define SpriteTilesheet_Screens_TestScreen_H_

#include <Ancona/Framework/Screens/AbstractScreen.hpp>
#include "../Input/SpriteTilesheetInputHandler.hpp"
#include "../Systems/SpriteTilesheetGameSystems.hpp"

namespace ild
{

/**
 * @brief Generated test screen for SpritesViaTileSheets
 */
class TestScreen : public AbstractScreen
{
    public:
        /**
         * @brief Constructs the test screen for SpritesViaTileSheets
         *
         * @param manager ScreenManager used by the game.
         * @param inputHandler InputHandler used by the screen.
         */
        TestScreen(
                ScreenManager & manager,
                SpriteTilesheetInputHandler * inputHandler);

        /**
         * @brief Will be called just before Update is called for the
         * first time.
         */
        void Init();

        /**
         * @brief Handles the update logic on the screen
         *
         * @param delta Seconds since last update.
         */
        void Update(float delta);

        /**
         * @brief Handles the draw logic on the screen
         *
         * @param delta Seconds since last draw.
         */
        void Draw(float delta);

        /* getters and setters */
        ScreenSystemsContainer * systemsContainer() override { return _systems.get(); }
    private:
        std::unique_ptr<SpriteTilesheetInputHandler> _inputHandler;
        std::unique_ptr<SpriteTilesheetGameSystems> _systems;
};

}

#endif
