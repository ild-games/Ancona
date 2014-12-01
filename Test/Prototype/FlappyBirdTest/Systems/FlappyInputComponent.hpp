#ifndef Ancona_Game_Systems_FlappyInputComponent_H_
#define Ancona_Game_Systems_FlappyInputComponent_H_

#include <Ancona/Engine/Core/Systems/PositionSystem.hpp>
#include <Ancona/Engine/Core/Systems/InputControlComponent.hpp>
#include "../InputDevices/FlappyKeyboard.hpp"


namespace ild
{

class FlappyInputComponent : public InputControlComponent
{

    public:
        FlappyInputComponent(
                Entity & flapper,
                PositionComponent & positionComponent,
                FlappyKeyboard & inputHandler);

        void Jump();
    private:
        PositionComponent & _positionComponent;

};

}

#endif
