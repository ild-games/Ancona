#ifndef Ancona_Game_Systems_KeyboardPlayerComponent_H_
#define Ancona_Game_Systems_KeyboardPlayerComponent_H_

#include <Ancona/Engine/Core/Systems/PositionComponent.hpp>

namespace ild
{

/**
 * @brief  Defines input logic for the player 
 *
 * @author Tucker Lein, Jeff Swenson
 */
class KeyboardPlayerComponent
{
    public:
        /**
         * @brief Create a KeyboardPlayerComponent that manipulates the player state.
         *
         * @param positionComponent The PositionComponent for the player.
         */
        KeyboardPlayerComponent(PositionComponent & positionComponent);

        /**
         * @brief Updates the player state based off keyboard state
         */
        void Update();
    private:
        /**
         * @brief Defines the position of the player
         */
        PositionComponent & _positionComponent;

        /**
         * @brief Scalar value desribing the speed of the player
         */
        const float SPEED = 0.1f;
};

}

#endif
