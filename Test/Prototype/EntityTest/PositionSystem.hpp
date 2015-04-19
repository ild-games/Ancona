#include <Ancona/Framework/EntityFramework/UnorderedSystem.hpp>

using namespace ild;

class PositionComponent
{

};

class PositionSystem : public UnorderedSystem<PositionComponent>
{
    public:
        PositionSystem(SystemManager & manager);

        void Update(float delta);

};
