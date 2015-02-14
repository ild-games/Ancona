
#include <gtest/gtest.h>

#include <Ancona/Engine/EntityFramework/SystemManager.hpp>
#include <Ancona/Engine/Core/Systems/Physics/PlatformPhysicsSystem.hpp>

using namespace ild;

TEST(PhysicsSystem, CreateMultipleComponents) {
    SystemManager manager;
    PlatformPhysicsSystem physics(manager);

    for(int i = 0; i < 5; i++)
    {
        Entity entity = manager.CreateEntity();
        physics.CreateComponent(entity);
    }

    ASSERT_TRUE(true);

}

TEST(PhysicsSystem, CreateMultipleComponentsWithGetPostion)
{
    SystemManager manager;
    PlatformPhysicsSystem physics(manager);

    for(int i = 0; i < 5; i++)
    {
        Entity entity = manager.CreateEntity();
        auto comp = physics.CreateComponent(entity);
        comp->GetInfo().GetPosition();
    }

    ASSERT_TRUE(true);

}

TEST(PhysicsSystem, CreateMultipleComponentsWithActions)
{
    SystemManager manager;
    PlatformPhysicsSystem physics(manager);

    for(int i = 0; i < 5; i++)
    {
        Entity entity = manager.CreateEntity();
        auto comp = physics.CreateComponent(entity);
        comp->GetActions().CreatePositionAction();
    }

    ASSERT_TRUE(true);

}
