#ifndef Ancona_Game_Systems_PlayerInputComponent_H_
#define Ancona_Game_Systems_PlayerInputComponent_H_

#include <Ancona/Engine/Core/Systems/PositionSystem.hpp>
#include <Ancona/Engine/Core/Systems/InputControlComponent.hpp>

namespace ild 
{

/**
 * @brief Contains the functions for manipulating the player's
 *        state based on input.
 *
 * @owner Tucker Lein
 */
class PlayerInputComponent : public InputControlComponent
{
    public:
        PlayerInputComponent(
                Entity & player, 
                PositionComponent & positionComponent);

        void Move();
                
    private:
};

}

#endif
