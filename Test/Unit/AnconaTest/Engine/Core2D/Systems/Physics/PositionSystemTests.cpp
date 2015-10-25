#include <gtest/gtest.h>

#include <Ancona/Core2D/Systems/Position/PositionSystem.hpp>
#include <Ancona/Framework/EntityFramework/SystemManager.hpp>

using namespace ild;

static UpdateStepEnum PHYSICS = UpdateStep::Physics;

class PositionSystemTest : public ::testing::Test {
protected:
    virtual void SetUp() override {
        entity = manager.CreateEntity();
        position = new PositionSystem("position", manager);
        posComp = position->CreateComponent(entity);
    }

    SystemManager manager;
    Entity entity;
    PositionSystem * position;
    PositionComponent * posComp;
};

TEST_F(PositionSystemTest, VelocityDefaultsToZero)
{
    ASSERT_EQ(Point(), posComp->position()) << "Position should start out as null";
    manager.Update(1, PHYSICS);
    ASSERT_EQ(Point(), posComp->position()) << "Zero velocity should not change the position";
}

TEST_F(PositionSystemTest, VelocityAppliedOnUpdate)
{
    auto vel = Point(10,100);
    posComp->velocity(vel);
    ASSERT_EQ(Point(), posComp->position()) << "Setting the velocity should not effect the position";
    manager.Update(1, PHYSICS);
    ASSERT_EQ(vel, posComp->velocity()) << "Update should not change the velocity";
    ASSERT_EQ(vel, posComp->position()) << "Update should change the velocity";
}
