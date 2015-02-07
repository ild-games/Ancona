#ifndef Ancona_Game_Screen_TestScreen_H_
#define Ancona_Game_Screen_TestScreen_H_

#include <Ancona/Engine/Screens/AbstractScreen.hpp>
#include <Ancona/Engine/EntityFramework/Entity.hpp>
namespace ild
{

class SystemManager;
class PositionSystem;
class InputControlSystem;
class DrawableSystem;

class TestScreen : public AbstractScreen
{
    public:
        TestScreen(ScreenManager & manager);

        void Update(float delta);

        void Init ();

        void Draw();
    private:
        SystemManager * _systemManager;
        PositionSystem  * _positionSystem;
        InputControlSystem * _inputSystem;
        DrawableSystem * _drawableSystem;
        Entity _player;
};

}

#endif

