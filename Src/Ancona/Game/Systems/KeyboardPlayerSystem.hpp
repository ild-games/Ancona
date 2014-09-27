#ifndef Ancona_Game_Systems_KeyboardPlayerSystem_H_
#define Ancona_Game_Systems_KeyboardPlayerSystem_H_

#include <Ancona/Engine/EntityFramework/UnorderedSystem.hpp>
#include <Ancona/Engine/Core/Systems/PositionSystem.hpp>
#include "KeyboardPlayerComponent.hpp"

namespace ild
{

/**
 * @brief  The keyboard player system allows the player to be manipulated by the keyboard 
 *
 * @author Tucker Lein
 */
class KeyboardPlayerSystem : UnorderedSystem<KeyboardPlayerComponent>
{
    public:
        /**
         * @brief Construct a keyboard player system and register it with the manager 
         *
         * @param manager Manager that the system belongs to.
         * @param positionSystem The system containing the positions of entities.
         */
        KeyboardPlayerSystem(SystemManager & manager, PositionSystem & positionSystem);

        /**
         * @brief Updates the system's components based off state of the keyboard.
         *
         * @param delta Seconds since last update.
         */
        void Update(float delta);

        /**
         * @brief  Create and attach a KeyboardPlayerComponent for the entity.
         *
         * @param  entity Entity that the component is attached to.
         *
         * @return A pointer to the KeyboardPlayerComponent.
         */
        KeyboardPlayerComponent * CreateComponent(const Entity & entity);

    private:
        /**
         * @brief Instance of the system holding position information for the game's entities.
         */
        PositionSystem & _positionSystem;
};

}

#endif
