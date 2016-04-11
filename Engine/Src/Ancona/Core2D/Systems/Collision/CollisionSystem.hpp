#ifndef Ancona_Engine_Core_Systems_Collision_CollisionSystem_H_
#define Ancona_Engine_Core_Systems_Collision_CollisionSystem_H_

#include <functional>
#include <map>
#include <vector>

#include <Ancona/Core2D/Systems/Position/PositionSystem.hpp>
#include <Ancona/Framework/EntityFramework/UnorderedSystem.hpp>
#include <Ancona/Util/Data.hpp>

#include "CollisionComponent.hpp"

namespace ild
{

/**
 * @brief Function signature used by the collision system.
 */
typedef std::function<void(const Entity&,const Entity&,const Point&,float)> CollisionCallback;

/**
 * @brief System used to provide collision interactions and callbacks for entities.
 * @author Jeff Swenson
 */
class CollisionSystem : public UnorderedSystem<CollisionComponent>
{
    public:
        /**
         * @brief Construct a collision system and register it with the manager.
         *
         * @param name The systems name used for loading.
         * @param manager Manager that the system belongs to.
         * @param positions System that defines the position of an entity.
         */
        CollisionSystem(const std::string & name, SystemManager & manager, PositionSystem & positions);

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
         * @param dim Dimension for the entity to be used for collision.
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
         * @param key describing the collision type.
         *
         * @return A unique Collision Type.
         */
        CollisionType CreateType(const std::string & key);

        /**
         * @brief Get the collision type associated with the key.
         */
        CollisionType GetType(const std::string & key);

        /**
         * @brief Get the key associated with the collision type.
         *
         * @type CollisionType used to get the key from.
         */
        std::string GetKeyFromType(const CollisionType & type);

        /**
         * @brief Define the handler that will be used for the collisions between the two types.
         *
         * @param typeA One type involved in the collision.
         * @param typeB The second type involved in the collision.
         * @param callback The callback will be called as callback(entityA, entityB) where
         *  entityA is an entity of the first type and entityB is an entity of second type.
         */
        void DefineCollisionCallback(CollisionType typeA, CollisionType typeB, CollisionCallback callback);

        /**
         * @brief Determine if the collision type has already been created.
         *
         * @param key Key that was used to create the collision type.
         *
         * @return True if the collision type is defined.  False otherwise.
         */
        bool IsCollisionTypeDefined(const std::string & key);

        /* Getters and Setters */
        PositionSystem & position() { return _positions; }
        void maxSlope(float value) { _maxSlope = value; }
    private:
        int _nextType;
        Table<CollisionCallback> _callbackTable;
        PositionSystem & _positions;
        std::unordered_map<std::string,CollisionType> _collisionTypes;
        std::unordered_map<CollisionType,std::string> _collisionTypeToKey;
        std::unordered_map<Entity, std::unordered_map<Entity, bool> > _lastCollisions;
        std::unordered_map<Entity, std::unordered_map<Entity, bool> > _currentCollisions;
        Point _leftGravityBound;
        Point _rightGravityBound;
        float _maxSlope = 45;

        bool UniqueCollision(const Entity & entityA, const Entity & entityB);
        void HandleCollision(
                EntityComponentPair &pairA,
                EntityComponentPair &pairB,
                const Point &fixNormal,
                float fixMagnitude);
        bool EntitiesOverlapping(float fixMagnitude);

        void UpdateGravityBounds();
        void FixCollision(EntityComponentPair & a, EntityComponentPair & b, const Point & fixNormal, float fixMagnitude);
        bool CollisionAllowed(EntityComponentPair & a, EntityComponentPair & b, const Point & finalNormal);
        bool IsOnGround(const Point & groundNormal);

        void PushApart(CollisionComponent * a, CollisionComponent * b, const Point & correctFix);
        void PushFirstOutOfSecond(CollisionComponent * a, CollisionComponent * b, const Point & correctFix);

};

}
#endif
