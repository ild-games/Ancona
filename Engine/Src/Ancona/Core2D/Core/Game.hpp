#ifndef Ancona_Engine_Core_Game_H_
#define Ancona_Engine_Core_Game_H_

#include <string>
#include <SFML/Graphics.hpp>
#include <Ancona/Framework/Screens/ScreenManager.hpp>

namespace ild
{

/**
 * @brief  Manages the game loop and game state
 *
 * @author Tucker Lein
 */
class Game
{
    public:
        /**
         * @brief Construct the Game
         */
        Game(int windowWidth, int windowHeight, const std::string & title);

        /**
         * @brief Begin the game loop, run the game
         */
        void Run();

    protected:
        /**
         * @brief Instance of the game manager
         */
        ScreenManager * _screenManager;

        /**
         * @brief Window used for rendering the game
         */
        sf::RenderWindow _window;

    private:
        void ProcessEvent(sf::Event event);
};

}

#endif
