#ifndef Ancona_Engine_Physics_BasePhysicsSystem_hpp
#define Ancona_Engine_Physics_BasePhysicsSystem_hpp

#include <Ancona/Engine/Core/Systems/Physics/Position.hpp>
#include <Ancona/Engine/EntityFramework/UnorderedSystem.hpp>

namespace ild
{

class BasePhysicsComponent
{
    public:
        /**
         * @brief Check if the entity is on the ground.
         *
         * @return True if the entity is on the ground.  False otherwise.
         */
        bool IsOnGround() const { return _isOnGround; }

        /**
         * @brief Get information about the Entities position.
         *
         * @return A constant reference to the position information.
         */
        const Position & GetInfo() const { return _position ; }

        /**
         * @brief Get a mutable copy of the entities position.  This should
         * be used with great care.  
         *
         * @return A mutable reference to the entities position.
         */
        Position & GetMutableInfo() { return _position; }

    protected:
        /**
         * @brief The position information for the component.
         */
        Position _position;

        /**
         * @brief Set if the entity is on the ground.
         *
         * @param value True if the entity is on the ground.  False otherwise.
         */
        inline void SetIsOnGround(bool value) { _isOnGround = value; }

    private:
        bool _isOnGround = false;
};

/**
 * @brief A Base Physics System that allows access 
 *  to information that is not closely tied to a games world.
 * @author Jeff Swenson
 */
class BasePhysicsSystem : public UnorderedSystem<BasePhysicsComponent>
{
    public:
        inline void SetGravity(Point gravity)
        {
            _gravity = gravity;
        }
        
        inline const Point & GetGravity()
        {
            return _gravity;
        }


    protected:
        /**
         * @brief Constructor of a BasePhysicsSystem and register it with the manager.  
         *
         * @param manager Manager that the system belongs to.
         */
        BasePhysicsSystem(SystemManager & manager);


        /**
         * @brief Update the physics components.  Must be implemented by the child physics system.
         *
         * @param delta Fraction of a second since the last update.
         */
        void Update(float delta) = 0;

    private:
        Point _gravity;
};

}
#endif
