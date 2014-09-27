#ifndef Ancona_Game_Core_AnconaGame_H_
#define Ancona_Game_Core_AnconaGame_H_

#include <Ancona/Engine/Core/Game.hpp>

namespace ild
{

class AnconaGame : public Game
{
    public:
        /**
         * @brief see ild.Game
         */
        AnconaGame(int windowWidth, int windowHeight, const std::string & title);

    protected:
        /**
         * @brief see ild.Game.CreateInitialScreen
         */
        void CreateInitialScreen();
};

}

#endif
