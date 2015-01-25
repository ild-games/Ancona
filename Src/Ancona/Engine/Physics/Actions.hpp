#ifndef Ancona_Engine_Physiscs_Actions_hpp
#define Ancona_Engine_Physiscs_Actions_hpp

#include <limits>
#include <vector>

#include <Ancona/Engine/Physics/Position.hpp>

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
        void Apply(Position & position, float delta);

        VectorActionProxy CreatePositionAction();
        VectorActionProxy CreateVelocityAction();
        VectorActionProxy CreateAccelerationAction();

    private:
        std::vector<VectorActionProxy> _positionActions;
        std::vector<VectorActionProxy> _velocityActions;
        std::vector<VectorActionProxy> _accelerationActions;
};

}
#endif
