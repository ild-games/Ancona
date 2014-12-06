#ifndef Ancona_Engine_Collision_CollisionComponent_H_
#define Ancona_Engine_Collision_CollisionComponent_H_

#include <Ancona/Engine/Core/Systems/PositionComponent.hpp>
#include <Ancona/Util/Collision/Box2.hpp>

namespace ild
{

typedef int CollisionType;

class CollisionComponent
{
    public:
        /**
         * @brief Construct a collision component.
         *
         * @param position The component describing the entities position.
         * @param dim A vector describing the entities dimmension.
         * @param type Type of entity for collisions.
         */
        CollisionComponent(PositionComponent & position, const sf::Vector3f & dim, CollisionType type ); 

        /**
         * @brief Test if the two collision components collide with eachother.
         *
         * @param otherComponent Component to test for collision.
         *
         * @return True if the components collide.  False otherwise.
         */
        bool Collides(const CollisionComponent & otherComponent);

        /**
         * @brief Update the internal state for purpose of collision.
         */
        void Update();

    private:
        PositionComponent & _position;
        Box2 _dim;
};

}
#endif
