#include <gtest/gtest.h>
#include <SFML/Graphics.hpp>

#include <Ancona/Core2D/Systems/Position/PositionSystem.hpp>
#include <Ancona/Core2D/Systems/Drawable/DrawableSystem.hpp>
#include <Ancona/Framework/EntityFramework/SystemManager.hpp>
#include <Ancona/Platformer/Actions/ActionSystem.hpp>

using namespace ild;

static UpdateStepEnum UPDATE = UpdateStep::Update;
static UpdateStepEnum PHYSICS = UpdateStep::Physics;

void update(SystemManager & manager, float delta)
{
    manager.Update(delta, UPDATE);
    manager.Update(delta, PHYSICS);
}

TEST(ActionSystem, CreateMultipleComponents)
{
    SystemManager manager;
    PositionSystem * position = new PositionSystem("position", manager);
    DrawableSystem * drawable = new DrawableSystem(
        "drawable", 
        *(new sf::RenderWindow(sf::VideoMode(100, 100), "test")), 
        manager);
    ActionSystem * action = new ActionSystem("action", manager, position, drawable);

    for (int i = 0; i < 5; i++)
    {
        Entity entity = manager.CreateEntity();
        action->CreateComponent(entity);
    }

    ASSERT_TRUE(true);
}

TEST(ActionSystem, CreateMultipleComponentsWithGetPostion)
{
    SystemManager manager;
    PositionSystem * position = new PositionSystem("position", manager);
    DrawableSystem * drawable = new DrawableSystem(
        "drawable", 
        *(new sf::RenderWindow(sf::VideoMode(100, 100), "test")), 
        manager);
    ActionSystem * action = new ActionSystem("action", manager, position, drawable);

    for (int i = 0; i < 5; i++)
    {
        Entity entity = manager.CreateEntity();
        auto comp = action->CreateComponent(entity);
        comp->actions();
    }

    ASSERT_TRUE(true);
}

TEST(ActionSystem, CreateMultipleComponentsWithActions)
{
    SystemManager manager;
    PositionSystem * position = new PositionSystem("position", manager);
    DrawableSystem * drawable = new DrawableSystem(
        "drawable", 
        *(new sf::RenderWindow(sf::VideoMode(100, 100), "test")), 
        manager);
    ActionSystem * action = new ActionSystem("action", manager, position, drawable);

    for (int i = 0; i < 5; i++)
    {
        Entity entity = manager.CreateEntity();
        auto comp = action->CreateComponent(entity);
        comp->actions().CreatePositionAction();
    }

    ASSERT_TRUE(true);
}

class ActionComponentTest : public ::testing::Test {
protected:
    virtual void SetUp() override {
        positionSys = new PositionSystem("position", manager);
        drawableSys = new DrawableSystem(
            "drawable", 
            *(new sf::RenderWindow(sf::VideoMode(100, 100), "test")), 
            manager);
        actionSys = new ActionSystem("action", manager, positionSys, drawableSys);
        entity = manager.CreateEntity();
        posComp = positionSys->CreateComponent(entity);
        actComp = actionSys->CreateComponent(entity);
        actComp->FetchDependencies(entity);
    }

    SystemManager manager;
    PositionSystem * positionSys;
    DrawableSystem * drawableSys;
    ActionSystem * actionSys;
    Entity entity;
    PositionComponent * posComp;
    ActionComponent * actComp;
};

TEST_F(ActionComponentTest, VelocityAction)
{
    auto action = actComp->actions().CreateVelocityAction();

    action->duration(1)
          ->value(Point(10,100));

    update(manager, 0);

    ASSERT_EQ(0, action->age()) << "The action is incorrectly aged";
    ASSERT_EQ(Point(10,100), posComp->velocity()) << "Velocity was not set correctly by the action.";

    update(manager, 0.5);

    ASSERT_EQ(0.5, action->age()) << "The action is incorrectly aged";
    ASSERT_FALSE(action->Done()) << "The action did not finish at the correct time";
    ASSERT_EQ(Point(10,100), posComp->velocity()) << "Velocity was removed too early.";
    ASSERT_EQ(Point(5,50), posComp->position()) << "Velocity did not correctly update the position.";

    update(manager, 1);

    ASSERT_EQ(1.5, action->age()) << "The action is incorrectly aged";
    ASSERT_TRUE(action->Done()) << "The action did not finish at the correct time";
    ASSERT_GT(Point(10,100).x, posComp->velocity().x) << "Velocity should be reduced if its duration"
        << " overflowed";
    ASSERT_GT(Point(10,100).y, posComp->velocity().y) << "Velocity should be reduced if its duration"
        << " overflowed";
    ASSERT_EQ(Point(10,100), posComp->position()) << "Velocity was applied for longer than"
        << " it should have been";
}

TEST_F(ActionComponentTest, PositionAction)
{
    auto action = actComp->actions().CreatePositionAction();

    action->value(Point(7,19));

    ASSERT_EQ(Point(), posComp->position()) << "The position should start out initalized to zero";

    update(manager, 1);

    ASSERT_EQ(1, action->age()) << "The age should have been updated during the update step";
    ASSERT_EQ(Point(7,19), posComp->position())
        << "The position should have been updated after the update phase";
}

TEST_F(ActionComponentTest, VelocityActionTween)
{
    auto action = actComp->actions().CreateVelocityAction();

    action
        ->duration(10)
        ->tween(1)
        ->value(Point(100,1000));

    ASSERT_EQ(Point(), posComp->velocity()) << "The starting velocity should be zero.";

    for(int i = 1; i <= 10; i++)
    {
        update(manager,0.10);
        ASSERT_NEAR((Point(10,100) * (float) i).x, posComp->velocity().x,1) << "The velocity is not tweening correctly";
        ASSERT_NEAR((Point(10,100) * (float) i).y, posComp->velocity().y,1) << "The velocity is not tweening correctly";
    }
}

TEST_F(ActionComponentTest, PositionActionTween)
{
    auto action = actComp->actions().CreatePositionAction();

    action
        ->duration(10)
        ->tween(1)
        ->value(Point(100,1000));

    ASSERT_EQ(Point(), posComp->position()) << "The starting position should be zero.";

    for(int i = 1; i <= 10; i++)
    {
        update(manager, 0.10);
        ASSERT_NEAR((Point(10,100) * (float) i).x, posComp->position().x,1) << "The position is not tweening correctly";
        ASSERT_NEAR((Point(10,100) * (float) i).y, posComp->position().y,1) << "The position is not tweening correctly";
    }
}

TEST_F(ActionComponentTest, PositionOverridesVelocity)
{
    auto posAction = actComp->actions().CreatePositionAction();
    posAction
        ->value(Point(100,0))
        ->duration(1);

    auto velAction = actComp->actions().CreateVelocityAction();
    velAction
        ->value(Point(0,10))
        ->duration(10);

    update(manager, 0.25);

    ASSERT_NEAR(0.25, posAction->age(), 0.01) << "The position's age did not update correctly";
    ASSERT_NEAR(0.25, velAction->age(), 0.01) << "The velocity's age did not update correctly";
    ASSERT_EQ(Point(100,0), posComp->position()) << "A velocity action should not"
        << "Change the position when there is a valid position.";

    update(manager, 1);

    ASSERT_NEAR(1.25, velAction->age(), 0.01) << "The velocity's age did not update correctly";
    ASSERT_NEAR(1.25, posAction->age(), 0.01) << "The position's age did not update correctly";

    update(manager, 1);

    ASSERT_NEAR(1.25, posAction->age(), 0.01) << "The position's age should not update once it is expired.";
    ASSERT_NEAR(2.25, velAction->age(), 0.01) << "The velocity's age did not update correctly";
    ASSERT_TRUE(posAction->Done()) << "The position action should be done";
    ASSERT_FALSE(velAction->Done()) << "The velocity action should be done";
    ASSERT_EQ(Point(100,0).x, posComp->position().x) << "The velocity should not have changed"
        << " the x position.";
    ASSERT_LT(Point(100,0).y, posComp->position().y) << "The velocity should be able to effect"
        << " the y position once the position action expires.";
}
