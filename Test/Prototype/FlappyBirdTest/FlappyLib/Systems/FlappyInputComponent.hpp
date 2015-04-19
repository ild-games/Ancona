#ifndef Ancona_Game_Systems_FlappyInputComponent_H_
#define Ancona_Game_Systems_FlappyInputComponent_H_

#include <Ancona/Framework/Core/Systems/PositionSystem.hpp>
#include <Ancona/Framework/Core/Systems/InputControlComponent.hpp>
#include "../InputDevices/FlappyInputHandler.hpp"
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
                FlappyInputHandler & inputHandler);

        void Jump();
    private:
        PositionComponent & _positionComponent;
        FlappyRotateComponent & _rotateComponent;

};

}

#endif
