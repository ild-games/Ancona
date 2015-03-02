#ifndef Ancona_Engine_Physiscs_Actions_hpp
#define Ancona_Engine_Physiscs_Actions_hpp

#include <limits>
#include <memory>
#include <vector>

#include <Ancona/Engine/Core/Systems/Physics/Position.hpp>
#include <Ancona/Engine/Core/Systems/Physics/VectorAction.hpp>
#include <Ancona/Engine/Core/Systems/Physics/BasePhysicsSystem.hpp>

namespace ild
{

namespace ActionDuration
{

const float PERSISTENT = std::numeric_limits<float>::infinity();
const float INSTANT = 0.0f;

}

typedef std::shared_ptr<VectorAction> VectorActionProxy;

/**
 * @brief Actions is used to contain all of the Actions that are effecting
 * an entity.  It also contains the logic for applying and updating the actions.
 * @author Jeff Swenson 
 */
class Actions
{
    public:
        /**
         * @brief Construct a container for actions.
         *
         * @param physicsSystem Physics system that the actions belong to.
         */
        Actions(BasePhysicsSystem & physicsSystem);

        /**
         * @brief Update the position based on active Actions in 
         * the object.
         *
         * @param position Position object to be updated.
         */
        void Apply(Position & position, float delta);

        /**
         * @brief Create an action for setting the position.
         *
         * @return A proxy to the position Action.
         */
        VectorActionProxy CreatePositionAction();

        /**
         * @brief Create an action for setting the velocity.
         *
         * @return A proxy to the velocity Action.
         */
        VectorActionProxy CreateVelocityAction();

        /**
         * @brief Used to set if an entity is effected by gravity.  Defaults to true.
         *
         * @param value Boolean value determining if the entity is effected by gravity.
         */
        void SetEffectedByGravity(bool value) { _effectedByGravity = value; }

        /**
         * @brief Remove any acceleration that has been caused by gravity.
         */
        void StopFall();
    private:

        /**
         * @brief Update the velocity based on Gravity.
         *
         * @param velocity Current velocity as determined by actions.
         */
        void ApplyGravity(Point & velocity, float delta);

        std::vector<VectorActionProxy> _positionActions;
        std::vector<VectorActionProxy> _velocityActions;
        Point _totalGravity;
        BasePhysicsSystem & _physicsSystem;
        bool _effectedByGravity = false;
        bool _onGround = false;
};

}
#endif
