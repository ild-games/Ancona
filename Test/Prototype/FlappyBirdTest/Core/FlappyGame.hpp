#ifndef Ancona_Game_Core_FlappyGame_H_
#define Ancona_Game_Core_FlappyGame_H_

#include <Ancona/Engine/Core/Game.hpp>
#include <Ancona/Game/Core/AnconaGame.hpp>
#include <Ancona/Engine/Resource/RequestList.hpp>

namespace ild
{

class FlappyGame : public AnconaGame
{
    public:
        /**
         * @brief see ild.Game
         */
        FlappyGame(int windowWidth, int windowHeight, const std::string & title);

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
