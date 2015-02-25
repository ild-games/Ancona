#ifndef Ancona_Engine_Core_Systems_Collision_CollisionComponent_H_
#define Ancona_Engine_Core_Systems_Collision_CollisionComponent_H_

#include <Ancona/Engine/Core/Systems/Physics/BasePhysicsSystem.hpp>
#include <Ancona/Util/Collision/Box2.hpp>

namespace ild
{

typedef int CollisionType;

namespace BodyType
{
    /**
     * @brief Enumeration that describes how the entity behaves in Solid body collision.
     * None - The entity does not take part in solid body collision
     * Solid - The entity
     * @author Jeff Swenson
     */
    enum Type
    {
        /**
         * @brief The entity does not take part in solid body collision.
         */
        None,
        /**
         * @brief The entity takes part in solid body collision and can be moved around.
         */
        Solid,
        /**
         * @brief The entity takes part in solid body collision, but it cannot be moved by a collision.
         */
        Environment,
        Count
    };
}
typedef BodyType::Type BodyTypeEnum;

/**
 * @brief Component attached to entities by the collision system.  It keeps track of state describing how the entity interacts
 * with other entities.
 * @author Jeff Swenson
 */
class CollisionComponent
{
    public:
        /**
         * @brief Construct a collision component.
         *
         * @param position The component describing the entities position.
         * @param dim A vector describing the entities dimmension.
         * @param type Type of entity for collisions.
         * @param bodyType BodyType of the collision component.  Determines how collision fixing is performed.
         */
        CollisionComponent(BasePhysicsComponent & position, const sf::Vector3f & dim, CollisionType type, BodyTypeEnum bodyType); 

        /**
         * @brief Test if the two collision components collide with eachother.
         *
         * @param otherComponent Component to test for collision.
         * @param fixVector Output variable used to return the vector used
         *  to fix the collision.
         *
         * @return True if the components collide.  False otherwise.
         */
        bool Collides(const CollisionComponent & otherComponent, Point & fixVector);

        /**
         * @brief Update the internal state for purpose of collision.
         */
        void Update();

        /**
         * @brief Return the Collision Type of the component
         *
         * @return Collision Type of the component.
         */
        CollisionType GetType();

        BodyTypeEnum GetBodyType() { return _bodyType; }

        BasePhysicsComponent & GetPhysicsComponent() { return _position; }

    private:
        BasePhysicsComponent & _position;
        Box2 _dim;
        CollisionType _type;
        BodyTypeEnum _bodyType;
};

}
#endif
