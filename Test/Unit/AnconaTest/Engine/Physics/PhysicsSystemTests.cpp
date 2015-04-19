
#include <gtest/gtest.h>

#include <Ancona/Engine/EntityFramework/SystemManager.hpp>
#include <Ancona/Platformer/Physics/PlatformPhysicsSystem.hpp>

using namespace ild;

UpdateStepEnum UPDATE = UpdateStep::Update;

TEST(PhysicsSystem, CreateMultipleComponents) {
    SystemManager manager;
    PlatformPhysicsSystem & physics = *(new PlatformPhysicsSystem("physics", manager));

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
    PlatformPhysicsSystem & physics = *(new PlatformPhysicsSystem("physics", manager));

    for(int i = 0; i < 5; i++)
    {
        Entity entity = manager.CreateEntity();
        auto comp = physics.CreateComponent(entity);
        comp->GetInfo().position();
    }

    ASSERT_TRUE(true);

}

TEST(PhysicsSystem, CreateMultipleComponentsWithActions)
{
    SystemManager manager;
    PlatformPhysicsSystem & physics = *(new PlatformPhysicsSystem("physics", manager));

    for(int i = 0; i < 5; i++)
    {
        Entity entity = manager.CreateEntity();
        auto comp = physics.CreateComponent(entity);
        comp->actions().CreatePositionAction();
    }

    ASSERT_TRUE(true);

}

TEST(PhysicsSystem, VelocityAction)
{
    SystemManager manager;
    PlatformPhysicsSystem & physics = *(new PlatformPhysicsSystem("physics", manager));
    Entity entity = manager.CreateEntity();
    PlatformPhysicsComponent * component = physics.CreateComponent(entity);

    auto action = component->actions().CreateVelocityAction();

    action->duration(1)
          ->value(Point(10,100));

    manager.Update(0,UPDATE);

    ASSERT_EQ(0, action->age()) << "The action is incorrectly aged";
    ASSERT_EQ(Point(10,100), component->GetInfo().velocity()) << "Velocity was not set correctly by the action.";

    manager.Update(0.5, UPDATE);

    ASSERT_EQ(0.5, action->age()) << "The action is incorrectly aged";
    ASSERT_FALSE(action->Done()) << "The action did not finish at the correct time";
    ASSERT_EQ(Point(10,100), component->GetInfo().velocity()) << "Velocity was removed too early.";
    ASSERT_EQ(Point(5,50), component->GetInfo().position()) << "Velocity did not correctly update the position.";

    manager.Update(1, UPDATE);

    ASSERT_EQ(1.5, action->age()) << "The action is incorrectly aged";
    ASSERT_TRUE(action->Done()) << "The action did not finish at the correct time";
    ASSERT_GT(Point(10,100).x, component->GetInfo().velocity().x) << "Velocity should be reduced if its duration"
        << " overflowed";
    ASSERT_GT(Point(10,100).y, component->GetInfo().velocity().y) << "Velocity should be reduced if its duration"
        << " overflowed";
    ASSERT_EQ(Point(10,100), component->GetInfo().position()) << "Velocity was applied for longer than"
        << " it should have been";
}

TEST(PhysicsSystem, PositionAction)
{
    SystemManager manager;
    PlatformPhysicsSystem & physics = *(new PlatformPhysicsSystem("physics", manager));
    Entity entity = manager.CreateEntity();
    PlatformPhysicsComponent * component = physics.CreateComponent(entity);

    auto action = component->actions().CreatePositionAction();

    action->value(Point(7,19));

    ASSERT_EQ(Point(), component->GetInfo().position()) << "The position should start out initalized to zero";
    manager.Update(1, UPDATE);

    ASSERT_EQ(1, action->age()) << "The age should have been updated during the update step";
    ASSERT_EQ(Point(7,19), component->GetInfo().position())
        << "The position should have been updated after the update phase";
}

TEST(PhysicsSystem, VelocityActionTween)
{
    SystemManager manager;
    PlatformPhysicsSystem & physics = *(new PlatformPhysicsSystem("physics", manager));
    Entity entity = manager.CreateEntity();
    PlatformPhysicsComponent * component = physics.CreateComponent(entity);

    auto action = component->actions().CreateVelocityAction();

    action
        ->duration(10)
        ->tween(1)
        ->value(Point(100,1000));

    ASSERT_EQ(Point(), component->GetInfo().velocity()) << "The starting velocity should be zero.";

    for(int i = 1; i <= 10; i++)
    {
        manager.Update(0.10, UPDATE);
        ASSERT_NEAR((Point(10,100) * (float) i).x, component->GetInfo().velocity().x,1) << "The velocity is not tweening correctly";
        ASSERT_NEAR((Point(10,100) * (float) i).y, component->GetInfo().velocity().y,1) << "The velocity is not tweening correctly";
    }
}

TEST(PhysicsSystem, PositionActionTween)
{
    SystemManager manager;
    PlatformPhysicsSystem & physics = *(new PlatformPhysicsSystem("physics", manager));
    Entity entity = manager.CreateEntity();
    PlatformPhysicsComponent * component = physics.CreateComponent(entity);

    auto action = component->actions().CreatePositionAction();

    action
        ->duration(10)
        ->tween(1)
        ->value(Point(100,1000));

    ASSERT_EQ(Point(), component->GetInfo().position()) << "The starting position should be zero.";

    for(int i = 1; i <= 10; i++)
    {
        manager.Update(0.10, UPDATE);
        ASSERT_NEAR((Point(10,100) * (float) i).x, component->GetInfo().position().x,1) << "The position is not tweening correctly";
        ASSERT_NEAR((Point(10,100) * (float) i).y, component->GetInfo().position().y,1) << "The position is not tweening correctly";
    }
}

TEST(PhysicsSystem, PositionOverridesVelocity)
{
    SystemManager manager;
    PlatformPhysicsSystem & physics = *(new PlatformPhysicsSystem("physics", manager));
    Entity entity = manager.CreateEntity();
    PlatformPhysicsComponent * component = physics.CreateComponent(entity);

    auto posAction = component->actions().CreatePositionAction();
    posAction
        ->value(Point(100,0))
        ->duration(1);

    auto velAction = component->actions().CreateVelocityAction();
    velAction
        ->value(Point(0,10))
        ->duration(10);

    manager.Update(0.25, UPDATE);

    ASSERT_NEAR(0.25, posAction->age(), 0.01) << "The position's age did not update correctly";
    ASSERT_NEAR(0.25, velAction->age(), 0.01) << "The velocity's age did not update correctly";
    ASSERT_EQ(Point(100,0), component->GetInfo().position()) << "A velocity action should not"
        << "Change the position when there is a valid position.";

    manager.Update(1, UPDATE);

    ASSERT_NEAR(1.25, velAction->age(), 0.01) << "The velocity's age did not update correctly";
    ASSERT_NEAR(1.25, posAction->age(), 0.01) << "The position's age did not update correctly";

    manager.Update(1, UPDATE);

    ASSERT_NEAR(1.25, posAction->age(), 0.01) << "The position's age should not update once it is expired.";
    ASSERT_NEAR(2.25, velAction->age(), 0.01) << "The velocity's age did not update correctly";
    ASSERT_TRUE(posAction->Done()) << "The position action should be done";
    ASSERT_FALSE(velAction->Done()) << "The velocity action should be done";
    ASSERT_EQ(Point(100,0).x, component->GetInfo().position().x) << "The velocity should not have changed"
        << " the x position.";
    ASSERT_LT(Point(100,0).y, component->GetInfo().position().y) << "The velocity should be able to effect"
        << " the y position once the position action expires.";
}

TEST(PhysicsSystem, RelativeToGroundMovement)
{
    Point ground1(1,0);
    Point velocity1(-3, 1);

    SystemManager manager;
    PlatformPhysicsSystem & physics = *(new PlatformPhysicsSystem("physics", manager));
    Entity entity = manager.CreateEntity();
    PlatformPhysicsComponent * component = physics.CreateComponent(entity);
    component->GetMutableInfo().groundDirection(ground1);

    manager.Update(1, UPDATE);

    ASSERT_EQ(component->GetInfo().groundDirection(), ground1) << "Ground direction should not change during the update";

    component->actions().CreateVelocityAction()
        ->isRelativeToGround(true)
        ->value(velocity1)
        ->duration(ActionDuration::PERSISTENT);

    manager.Update(1, UPDATE);

    ASSERT_EQ(Point(0,-3), component->GetInfo().position()) << "The position was not updated based on the ground vector";
}
