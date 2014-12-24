#ifndef Ancona_Game_Core_AnconaGame_H_
#define Ancona_Game_Core_AnconaGame_H_

#include <Ancona/Engine/Core/Game.hpp>
#include <Ancona/Engine/Resource/RequestList.hpp>

namespace ild
{

class AnconaGame : public Game
{
    public:
        AnconaGame(int windowWidth, int windowHeight, const std::string & title);

        ~AnconaGame();

    protected:

        void CreateInitialScreen();

    private:

        RequestList * _requestList;


};

}

#endif