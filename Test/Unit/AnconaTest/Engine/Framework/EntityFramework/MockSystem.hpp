#ifndef AnconaTest_Engine_EntityFramework_H_
#define AnconaTest_Engine_EntityFramework_H_

#include <Ancona/Framework/EntityFramework/UnorderedSystem.hpp>

namespace ild
{

class MockComponent
{
    public:
        MockComponent();
        bool WasUpdated();
        void ClearUpdate();
        void Update();
    private:
        bool _wasUpdated;
};

class MockSystem : public UnorderedSystem<MockComponent>
{
    public:
        MockSystem(SystemManager & manager);

        void Update(float delta);

        MockComponent * CreateComponent(const Entity & entity);

        int ComponentCount();

        void OnComponentRemove(Entity entity, MockComponent * component);

        bool ComponentRemoved;
};

}
#endif
