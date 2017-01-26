#ifndef Ancona_Platformer_Physiscs_Actions_hpp
#define Ancona_Platformer_Physiscs_Actions_hpp

#include <limits>
#include <memory>
#include <vector>

#include <Ancona/Core2D/Systems/Position/PositionSystem.hpp>

#include "VectorAction.hpp"

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
         * @copydoc ild::CameraComponent::Serialize
         */
        void Serialize(Archive & arc);

        void position(PositionSystem * positionSystem) { _positionSystem = positionSystem; }

    private:
        std::vector<VectorActionProxy> _positionActions;
        std::vector<VectorActionProxy> _velocityActions;
        Point _actionVelocity;
        PositionSystem * _positionSystem;

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

        Point ApplyPositionActions(const PositionComponent & position, float delta);
        Point ApplyVelocityActions(const PositionComponent & position, float delta);
};

}
#endif
