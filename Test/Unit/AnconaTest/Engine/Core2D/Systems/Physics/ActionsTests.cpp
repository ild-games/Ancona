#include <iostream>

#include <gtest/gtest.h>

#include <Ancona/Platformer/Actions/Actions.hpp>

using namespace ild;

TEST(Actions, Builder_Priority_Duration_Value) {
    VectorAction action;
    action.priority(1)
            ->duration(10)
            ->value(Point(5, 7));

    ASSERT_EQ(action.priority(),1) << "The builder priority method failed.";
    ASSERT_EQ(action.duration(),10) << "The builder duration method failed.";
    ASSERT_EQ(action.value(),Point(5,7)) << "The builder value method failed.";
}

TEST(Actions, Age_Done)
{
    VectorAction action;
    action.duration(10);

    action.Update(5);

    ASSERT_EQ(action.age(),5) << "Update does not correctly age the Action.";
    ASSERT_FALSE(action.Done()) << "Action is prematurely Done.";
    
    action.Update(6);

    ASSERT_EQ(action.age(),11) << "Second update did not correctly age the Action.";
    ASSERT_TRUE(action.Done()) << "The action should be done after it has aged more than the duration.";
}

TEST(Actions, ZeroTween)
{
    VectorAction action;
    action.value(Point(10, 100))
            ->duration(1);

    ASSERT_EQ(action.tweenRatio(), 1) << "Default tween ratio should be 1";

    action.Update(0);

    ASSERT_EQ(action.tweenRatio(), 1) << "Default tween ratio should be 1";
}

TEST(Actions, Tween) 
{
    VectorAction action;
    action.value(Point(10, 100))
            ->duration(4)
            ->tween(2);

    ASSERT_EQ(action.tweenRatio(), 0) << "Incorrect tween ratio";

    action.Update(0.5); 
    ASSERT_EQ(action.tweenRatio(), 0.25) << "Incorrect tween ratio";

    action.Update(0.5);
    ASSERT_EQ(action.tweenRatio(), 0.5) << "Incorrect tween ratio";

    action.Update(1);
    ASSERT_EQ(action.tweenRatio(), 1) << "Incorrect tween ratio";

    action.Update(1);
    ASSERT_EQ(action.tweenRatio(), 1) << "Incorrect tween ratio";
}

TEST(Actions, ResetAge)
{
    VectorAction action;
    action.value(Point(10, 100))
            ->duration(4)
            ->tween(2);

    ASSERT_EQ(action.tweenRatio(), 0) << "Incorrect tween ratio";

    action.Update(1);

    ASSERT_EQ(action.tweenRatio(), 0.5) << "Incorrect tween ratio";

    action.ResetAge();

    ASSERT_EQ(action.age(), 0) << "The age reset did not reset the age";
    ASSERT_EQ(action.tweenRatio(), 0) << "The age reset did not reset the tween";

}
