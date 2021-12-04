#ifndef Ancona_Engine_Screen_ScreenManager_H_
#define Ancona_Engine_Screen_ScreenManager_H_

#include <stack>

#include <Ancona/HAL.hpp>

namespace ild
{

class AbstractScreen;

/**
 * @brief  Responsible for managing all the screens that are loaded into the system.
 *         Screen are stored using stock logic, with the stack order being the order
 *         the screen were added to the system. This means the screen at the top of the stack
 *         is the current screen being run by the game, but when that screen exits it
 *         gets popped off the stack and the screen below it is then the inactive screen.
 *
 * @author Tucker Lein
 */
class ScreenManager
{
  public:
    /**
     * @brief Construct the ScreenManager
     *
     * @param window the window for the game
     * @param windowWidth the intended render width of the window
     * @param windowHeight the intended render height of the window
     */
    ScreenManager(ildhal::Window &window, int windowWidth, int windowHeight);
    ~ScreenManager();

    /**
     * @brief Pushes a new screen either with a loading screen or without one.
     *
     * @param screen Screen to load.
     * @param load True if the screen requires loading, otherwise false. Defaults to true.
     */
    void Push(AbstractScreen *screen, bool load = true);

    /**
     * @brief Pops the current screen off the manager. This removes the reference
     * to the screen and deletes the pointer.
     */
    void Pop();
    void PopImmediate();
    AbstractScreen *Peek();

    /**
     * @brief Pops the current screen off the manager and pushes a new one on
     *
     * @param screen Screen to push
     */
    void Replace(AbstractScreen *screen);

    void InputUpdate(float delta);
    /**
     * @brief Updates the current screen
     *
     * @param delta time since last update
     */
    void Update(float delta);

    /**
     * @brief Renders the current screen.
     *
     * @param delta time since last Draw.
     */
    void Draw(float delta);

    /**
     * @brief  Checks if the screen manager has any screens
     *         to run.
     *
     * @return True if there aren't any screens on the
     *         stack, otherwise false.
     */
    bool Empty();

    /**
     * @brief The window instance for the game
     */
    ildhal::Window &Window;

    /* getters and setters */
    int windowWidth() const
    {
        return _windowWidth;
    }
    int windowHeight() const
    {
        return _windowHeight;
    }

  private:
    /**
     * @brief The current screens being managed, in the order they were added
     */
    std::stack<AbstractScreen *> _screens;
    /**
     * @brief Screen that will be replacing the current screen after the exiting function has finished.
     */
    AbstractScreen *_replacementScreen = nullptr;
    /**
     * @brief windowWidth the intended render width of the window
     */
    int _windowWidth;
    /**
     * @brief windowHeight the intended render height of the window
     */
    int _windowHeight;

    /**
     * @brief called when the screen has been popped and the exit code has finished.
     */
    void RemoveScreen();
    void SaveScreen();
};

} // namespace ild

#endif
