#ifndef JumpyDuck_Screens_Systems_HPP
#define JumpyDuck_Screens_Systems_HPP

#include <memory>

#include <Ancona/Engine/Screens/AbstractScreen.hpp>
#include "../Systems/JumpyGameSystems.hpp"

namespace ild
{

class JumpyScreen : public AbstractScreen
{
    public:
        JumpyScreen(ScreenManager & manager);

        void Update(float delta);

        void Init();

        void Draw(float delta);

        /* getters and setters */
        ScreenSystemsContainer * GetSystemsContainer() override { return _systems.get(); }
    private:
        std::unique_ptr<JumpyGameSystems> _systems;

        Entity player;
        Entity defaultCam;

};

}
#endif
