#ifndef Ancona_Game_Core_FlappyGame_H_
#define Ancona_Game_Core_FlappyGame_H_

#include <Ancona/Engine/Core/Game.hpp>
#include <Ancona/Game/Core/AnconaGame.hpp>
#include <Ancona/Engine/Resource/RequestList.hpp>
#include "../InputDevices/FlappyInputHandler.hpp"
#include "FactoryBase.hpp"

namespace ild
{

class FlappyGame : public Game
{
    public:
        /**
         * @brief see ild.Game
         */
        FlappyGame(
                int windowWidth, 
                int windowHeight, 
                const std::string & title,
                FactoryBase * platformFactory);

    protected:
        /**
         * @brief see ild.Game.CreateInitialScreen
         *
         * @param inputHandler InputHandler used for game
         */
        void CreateInitialScreen();

    private:
        /**
         * @brief Initial RequestList for the game.
         */
        RequestList * _requestList;

        /**
         * @brief Factory for all platform dependent objs.
         */
        FactoryBase * _platformFactory;
};

}

#endif
