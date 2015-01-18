#ifndef Ancona_Game_Core_AnconaGame_H_
#define Ancona_Game_Core_AnconaGame_H_

#include <Ancona/Engine/Core/Game.hpp>
#include <Ancona/Engine/Resource/RequestList.hpp>

namespace ild
{

class AnconaGame : public Game
{
    public:
        /**
         * @brief see ild.Game
         */
        AnconaGame(int windowWidth, int windowHeight, const std::string & title);

        /**
         * @brief Destructor for AnconaGame
         */
        ~AnconaGame();

    protected:
        /**
         * @brief see ild.Game.CreateInitialScreen
         */
        virtual void CreateInitialScreen();

    private:
        /**
         * @brief Initial RequestList for the game.
         */
        RequestList * _requestList;
};

}

#endif
