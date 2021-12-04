#ifndef Anona_Menu_Screens_Menu_MenuScreen_H_
#define Anona_Menu_Screens_Menu_MenuScreen_H_

#include <Ancona/Framework/Screens/AbstractScreen.hpp>

#include "MenuGameSystems.hpp"
#include "MenuInputHandler.hpp"

namespace ild
{

typedef std::function<void(std::string)> ButtonPressedCallback;

/**
 * @brief A screen that can be used to show a menu.
 */
class MenuScreen : public ild::AbstractScreen
{
  public:
    /**
     * @brief Constructs the menu screen.
     *
     * @param ButtonPressedCallback called during the screen update step if a button was pressed.
     *                              The game should use this to handle the button press. The buttonKey of the pressed
     *                              button is provided as an argument.
     * @param mapKey The menu screen will load the map file specified by key.
     * @param manager ScreenManager used by the game.
     * @param inputHandler InputHandler used by the screen.
     */
    MenuScreen(ButtonPressedCallback buttonPressed, std::string mapKey, ild::ScreenManager &manager,
               std::shared_ptr<MenuInputHandler> inputHandler);

    /**
     * @brief Will be called just before Update is called for the
     * first time.
     */
    void Init() override;

    void InputUpdate(float delta) override;
    /**
     * @brief Handles the update logic on the screen
     *
     * @param delta Seconds since last update.
     */
    void Update(float delta) override;

    /**
     * @brief Handles the draw logic on the screen
     *
     * @param delta Seconds since last draw.
     */
    void Draw(float delta) override;

    /* getters and setters */
    ild::ScreenSystemsContainer *systemsContainer() override
    {
        return _systems.get();
    }

  private:
    ButtonPressedCallback _buttonPressed;
    std::shared_ptr<MenuInputHandler> _inputHandler;
    std::unique_ptr<MenuGameSystems> _systems;
};

} // namespace ild

#endif
