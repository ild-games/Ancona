#ifndef Ancona_Engine_Core_Systems_Collision_CollisionComponent_H_
#define Ancona_Engine_Core_Systems_Collision_CollisionComponent_H_

#include <vector>

#include <Ancona/Core2D/Systems/Position/PositionSystem.hpp>
#include <Ancona/Util2D/Collision/Box2.hpp>
#include <Ancona/Util/Data.hpp>

#include "Collision.hpp"

namespace ild
{

typedef int CollisionType;
class CollisionSystem;

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
        /*
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
         * @param collisionSystem The system describing the entities position.
         * @param dim A vector describing the entities dimmension.
         * @param type Type of entity for collisions.
         * @param bodyType BodyType of the collision component.  Determines how collision fixing is performed.
         */
        CollisionComponent(CollisionSystem * collisionSystem, const sf::Vector3f & dim, CollisionType type, BodyTypeEnum bodyType);

        /*
         * Constructor that should only be used by the loading system.
         */
        CollisionComponent() {};

        /**
         * @brief Test if the two collision components collide with eachother.
         *
         * @param otherComponent Component to test for collision.
         * @param fixNormal Output variable used to return the normal used
         *  to fix the collision.
         * @param fixMagnitude Magnitude of the vector used to push the objects apart.
         *
         * @return True if the components collide.  False otherwise.
         */
        bool Collides(const CollisionComponent & otherComponent, Point & fixNormal, float & fixMagnitude) const;

        /**
         * @brief Update the internal state for purpose of collision.
         */
        void Update();

        /**
         * @copydoc ild::CameraComponent::FetchDependencies
         */
        void FetchDependencies(const Entity & entity);

        /**
         * @copydoc ild::CameraComponent::Serialize
         */
        void Serialize(Archive & arc);

        /**
         * Update the collision box based on the entity's current position.
         */
        void UpdateDimensionPosition();

        /**
         * Get all of the collisions involving the component.
         * @return A vector of collisions.
         */
        std::vector<Collision> GetCollisions() const;

        /**
         * Get all of the collisions involving the component and override the component's collision box.
         * @return a Vector of collisions;
         */
        std::vector<Collision> GetCollisions(const Box2 & boxToTest) const;

        /* getters and setters */
        CollisionType type();
        BodyTypeEnum bodyType() const { return _bodyType; }
        void bodyType(BodyTypeEnum bodyType) { _bodyType = bodyType; }
        PositionComponent & positionComponent() { return *_position; }
        const Box2 & box() const { return _dim; }
        void anchor(const sf::Vector2f & anchor) { _anchor = anchor; }
        const sf::Vector2f & anchor() { return _anchor; }

    private:
        PositionComponent * _position;
        CollisionSystem * _system;
        Box2 _dim;
        CollisionType _type;
        BodyTypeEnum _bodyType;
        sf::Vector2f _anchor;
};


}

namespace std {
    template <> struct hash<ild::BodyTypeEnum> {
            std::size_t operator()(ild::BodyTypeEnum const& key) const
            {
                return key;
            }
    };
} /* std */
#endif
