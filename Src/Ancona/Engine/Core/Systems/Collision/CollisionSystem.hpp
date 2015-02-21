#ifndef Ancona_Engine_Core_Systems_Collision_CollisionSystem_H_
#define Ancona_Engine_Core_Systems_Collision_CollisionSystem_H_

#include <vector>
#include <functional>

#include <Ancona/Engine/EntityFramework/UnorderedSystem.hpp>
#include <Ancona/Engine/Core/Systems/Physics/BasePhysicsSystem.hpp>
#include "CollisionComponent.hpp"

namespace ild
{

typedef std::function<void(const Entity&,const Entity&)> CollisionCallback;


class CollisionSystem : public UnorderedSystem<CollisionComponent>
{
    public:
        /**
         * @brief Construct a collision system and register it with the manager.
         *
         * @param manager Manager that the system belongs to.
         * @param positions System that defines the position of an entity.
         */
        CollisionSystem(SystemManager & manager, BasePhysicsSystem & positions);

        /**
         * @brief Update the position for all components based off of their velocity
         *
         * @param delta Number of ms since last update
         */
        void Update(float delta);

        /**
         * @brief Create and attach a collision component for the entity.
         *
         * @param entity Entity that the component is attached to.
         * @param dim Dimmension for the entity to be used for collision.
         * @param type The collision type of the entity.
         * @param bodyType The body type of the entity.  Determines how collision fixing
         *  is handled for it. Defaults to BodyType::None.
         *
         * @return A pointer to the component.
         */
        CollisionComponent * CreateComponent(const Entity & entity,
                const sf::Vector3f & dim,
                CollisionType type,
                BodyTypeEnum bodyType = BodyType::None);

        /**
         * @brief Create a Type that can be assigned to a component.
         *
         * @return A unique Collision Type.
         */
        CollisionType CreateType();

        /**
         * @brief Set a handler for collisions between the two types.
         *
         * @param typeA One type involved in the collision.
         * @param typeB The second type involved in the collision.
         * @param callback The callback will be called as callback(entityA, entityB) where
         *  entityA is an entity of the first type and entityB is an entity of second type.
         */
        void SetHandler(CollisionType typeA, CollisionType typeB, CollisionCallback callback);
    private:
        int _nextType;
        std::vector< std::vector<CollisionCallback> > _callbackTable;
        BasePhysicsSystem & _positions;
};

}
#endif
