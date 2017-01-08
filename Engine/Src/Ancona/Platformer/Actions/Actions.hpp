#ifndef Ancona_Platformer_Physiscs_Actions_hpp
#define Ancona_Platformer_Physiscs_Actions_hpp

#include <limits>
#include <memory>
#include <vector>

#include <Ancona/Core2D/Systems/Position/PositionSystem.hpp>

#include "VectorAction.hpp"
#include "JumpAction.hpp"
#include "RunAction.hpp"

namespace ild
{

namespace ActionDuration
{

const float PERSISTENT = std::numeric_limits<float>::infinity();
const float INSTANT = 0.0f;

}

typedef std::shared_ptr<VectorAction> VectorActionProxy;
typedef std::shared_ptr<JumpAction> JumpActionProxy;
typedef std::shared_ptr<RunAction> RunActionProxy;

/**
 * @brief Actions is used to contain all of the Actions that are effecting
 * an entity.  It also contains the logic for applying and updating the actions.
 * @author Jeff Swenson
 */
class Actions
{
    public:
        /**
         * @brief Default constructor that should only be used for serialization.
         */
        Actions() {}

        /**
         * @brief Construct a container for actions.
         *
         * @param positionSystem Action system that the actions belong to.
         */
        Actions(PositionSystem * positionSystem);

        /**
         * @brief Update the position based on inactive Actions in
         * the object.
         *
         * @param position Position object to be updated.
         */
        void Apply(PositionComponent & position, float delta);

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
         * @brief Create a jump action for entities that can jump.
         *
         * @return A proxy to the jump action
         */
        JumpActionProxy CreateJumpAction();

        /**
         * @brief Create a run action for entities that can run.
         *
         * @return A proxy to the run action
         */
        RunActionProxy CreateRunAction(PositionComponent * positionComponent);

        /**
         * @copydoc ild::CameraComponent::Serialize
         */
        void Serialize(Archive & arc);

        /**
         * @brief Used to set if an entity is affected by gravity.  Defaults to true.
         *
         * @param value Boolean value determining if the entity is affected by gravity.
         */
        void SetAffectedByGravity(bool value) { _affectedByGravity = value; }

        /**
         * @brief Remove any acceleration that has been caused by gravity.
         */
        void StopFall();

        /* Getters and Setters */
        void position(PositionSystem * positionSystem) { _positionSystem = positionSystem; }
        const Point & totalGravity() { return _totalGravity; }

    private:
        std::vector<VectorActionProxy> _positionActions;
        std::vector<VectorActionProxy> _velocityActions;
        std::vector<JumpActionProxy> _jumpActions;
        std::vector<RunActionProxy> _runActions;
        Point _actionVelocity;
        Point _totalGravity;
        PositionSystem * _positionSystem;
        bool _affectedByGravity = false;

        template<typename T>
        void RemoveDoneActions(std::vector<T> & actions)
        {
            actions.erase(
                alg::remove_if(
                    actions,
                    [](T & action) { return action->Done(); }
                    ),
                actions.end()
                );
        }

        /**
         * @brief Update the velocity based on Gravity.
         *
         * @param velocity Current velocity as determined by actions.
         */
        void ApplyGravity(Point & velocity, float delta);

        Point ApplyPositionActions(const PositionComponent & position, float delta);
        Point ApplyVelocityActions(const PositionComponent & position, float delta);
        void ApplyJumpActions();
        void ApplyRunActions();

};

}
#endif
