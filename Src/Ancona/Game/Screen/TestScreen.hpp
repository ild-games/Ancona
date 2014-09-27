#ifndef Ancona_Game_Screen_TestScreen_H_
#define Ancona_Game_Screen_TestScreen_H_

#include <Ancona/Engine/Screen/AbstractScreen.hpp>

namespace ild
{

class SystemManager;
class PositionSystem;
class KeyboardPlayerSystem;

class TestScreen : public AbstractScreen
{
    public:
        TestScreen(ScreenManager & manager);

        void Update(float delta);

        void Draw();
    private:
        SystemManager * _systemManager;
        PositionSystem  * _positionSystem;
        KeyboardPlayerSystem * _keyboardPlayerSystem;
};

}

#endif

