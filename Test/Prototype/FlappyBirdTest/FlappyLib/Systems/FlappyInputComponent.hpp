#ifndef Ancona_Game_Systems_FlappyInputComponent_H_
#define Ancona_Game_Systems_FlappyInputComponent_H_

#include <Ancona/Engine/Core/Systems/PositionSystem.hpp>
#include <Ancona/Engine/Core/Systems/InputControlComponent.hpp>
#include "../InputDevices/FlappyTouch.hpp"
#include "../InputDevices/FlappyKeyboard.hpp"
#include "FlappyRotateComponent.hpp"


namespace ild
{

class FlappyInputComponent : public InputControlComponent
{

    public:
        FlappyInputComponent(
                Entity & flapper,
                PositionComponent & positionComponent,
                FlappyRotateComponent & rotateComponent,
                FlappyTouch & inputHandler);

        FlappyInputComponent(
                Entity & flapper,
                PositionComponent & positionComponent,
                FlappyRotateComponent & rotateComponent,
                FlappyKeyboard & inputHandler);

        void Jump();
    private:
        PositionComponent & _positionComponent;
        FlappyRotateComponent & _rotateComponent;

};

}

#endif
