#ifndef Ancona_Engine_Core_Game_H_
#define Ancona_Engine_Core_Game_H_

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include <Ancona/Framework/Screens/ScreenManager.hpp>
#include <Ancona/HAL/Window.hpp>

namespace ild {

/**
 * @brief  Manages the game loop and game state
 *
 * @author Tucker Lein
 */
class Game {
public:
    /**
     * @brief Construct the Game
     */
    Game(int windowWidth, int windowHeight, const std::string& title, const sf::Uint32& style = sf::Style::Default);

    /**
     * @brief Begin the game loop, run the game
     */
    void Run();

    virtual ~Game();

    static unsigned int FrameCount;

    /* getters and setters */
    const bool& windowIsActive() const { return _windowIsActive; }
    ScreenManager& screenManager() { return *_screenManager; }

protected:
    /**
     * @brief Instance of the game manager
     */
    std::unique_ptr<ScreenManager> _screenManager;

    /**
     * @brief Window used for rendering the game
     */
    sf::RenderWindow _window;

    std::unique_ptr<Window> _ildWindow;

private:
    void ProcessWindowEvent(sf::Event event);

    bool _windowIsActive = true;
};
}

#endif
