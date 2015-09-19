#ifndef Ghosted_Screens_TestScreen_H_
#define Ghosted_Screens_TestScreen_H_

#include <Ancona/Framework/Screens/AbstractScreen.hpp>
#include "../Input/GhostedInputHandler.hpp"
#include "../Systems/GhostedGameSystems.hpp"

namespace ild
{

/**
 * @brief Generated test screen for Ghosted
 */
class TestScreen : public AbstractScreen
{
    public:
        /**
         * @brief Constructs the test screen for Ghosted
         *
         * @param manager ScreenManager used by the game.
         * @param inputHandler InputHandler used by the screen.
         */
        TestScreen(
                ScreenManager & manager,
                GhostedInputHandler * inputHandler);

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
        std::unique_ptr<GhostedInputHandler> _inputHandler;
        std::unique_ptr<GhostedGameSystems> _systems;
};

}

#endif
