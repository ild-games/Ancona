#ifndef Ancona_Engine_Core_Systems_SpriteSystem_H_
#define Ancona_Engine_Core_Systems_SpriteSystem_H_

#include <string>
#include <SFML/Window.hpp>
#include <Ancona/Engine/EntityFramework/UnorderedSystem.hpp>
#include <Ancona/Engine/Resource/ResourceLibrary.hpp>
#include "PositionSystem.hpp"
#include "SpriteComponent.hpp"

namespace ild
{

/**
 * @brief The SpriteSystem is used to draw and animate basic sprite entities
 *
 * @author Jeff Swenson
 */
class SpriteSystem : public UnorderedSystem<SpriteComponent>
{
    public:
        /**
         * @brief Create and initialize a sprite system.
         *
         * @param window Window that the sprites should be drawn to.
         * @param systemManager System Manager that the system belongs to.
         * @param positionSystem Position System that defines the entities position.
         */
        SpriteSystem(sf::RenderWindow & window, 
                SystemManager & systemManager, 
                PositionSystem & positionSystem);

        /**
         * @brief Create a sprite component for the entity.
         *
         * @param entity Entity that the component should be attached to.
         * @param textureKey Key that describes the texture the sprite should use.
         * @param priority RenderPriority that handles when the sprite is drawn.
         *
         * @return A pointer to the newly created sprite.
         */
        SpriteComponent * CreateComponent(
                const Entity & entity, 
                const std::string & textureKey,
                const RenderPriorityEnum priority,
                int priorityOffset = 0);

        /**
         * @brief Draw all sprites to the screen.
         *
         * @param delta Ignored by the sprite system.
         */
        void Update(float delta);

    protected:
        /**
         * @see ild::SystemManager::OnComponentRemove(Entity, ComponentType*)
         */
        void OnComponentRemove(Entity entity, SpriteComponent * component);

    private:
        /**
         * @brief The window the sprite system will draw to.
         */
        sf::RenderWindow & _window;
        /**
         * @brief The system used to determine where an entity should be drawn.
         */
        PositionSystem & _positionSystem;

        /**
         * @brief Holds pointers to the sprite components sorted by priority + priorityOffset.
         */
        std::vector<SpriteComponent * > _renderQueue;
};

}

#endif
