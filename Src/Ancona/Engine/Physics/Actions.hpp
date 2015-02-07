#ifndef Ancona_Engine_Physiscs_Actions_hpp
#define Ancona_Engine_Physiscs_Actions_hpp

#include <limits>
#include <memory>
#include <vector>

#include <Ancona/Engine/Physics/Position.hpp>
#include <Ancona/Engine/Physics/VectorAction.hpp>

namespace ild
{

namespace ActionDuration
{

const float PERSISTENT = std::numeric_limits<float>::infinity();
const float INSTANT = 0.0f;

}

typedef std::shared_ptr<VectorAction> VectorActionProxy;

class Actions
{
    public:
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

    private:
        std::vector<VectorActionProxy> _positionActions;
        std::vector<VectorActionProxy> _velocityActions;
};

}
#endif
