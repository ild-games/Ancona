#include <iostream>

#include <gtest/gtest.h>

#include <Ancona/Engine/Core/Systems/Physics/Actions.hpp>

using namespace ild;

TEST(Actions, Builder_Priority_Duration_Value) {
    VectorAction action;
    action.Priority(1)
        ->Duration(10)
        ->Value(Point(5,7));

    ASSERT_EQ(action.GetPriority(),1) << "The builder Priority method failed."; 
    ASSERT_EQ(action.GetDuration(),10) << "The builder Duration method failed."; 
    ASSERT_EQ(action.GetValue(),Point(5,7)) << "The builder Value method failed."; 
}

TEST(Actions, Age_Done)
{
    VectorAction action;
    action.Duration(10);

    action.Update(5);

    ASSERT_EQ(action.GetAge(),5) << "Update does not correctly age the Action.";
    ASSERT_FALSE(action.Done()) << "Action is prematurely Done.";
    
    action.Update(6);

    ASSERT_EQ(action.GetAge(),11) << "Second update did not correctly age the Action.";
    ASSERT_TRUE(action.Done()) << "The action should be done after it has aged more than the Duration.";
}

TEST(Actions, ZeroTween)
{
    VectorAction action;
    action.Value(Point(10,100))
        ->Duration(1);

    ASSERT_EQ(action.GetTweenRatio(), 1) << "Default tween ratio should be 1";

    action.Update(0);

    ASSERT_EQ(action.GetTweenRatio(), 1) << "Default tween ratio should be 1";
}

TEST(Actions, Tween) 
{
    VectorAction action;
    action.Value(Point(10,100))
        ->Duration(4)
        ->Tween(2);

    ASSERT_EQ(action.GetTweenRatio(), 0) << "Incorrect tween ratio";

    action.Update(0.5); 
    ASSERT_EQ(action.GetTweenRatio(), 0.25) << "Incorrect tween ratio";

    action.Update(0.5);
    ASSERT_EQ(action.GetTweenRatio(), 0.5) << "Incorrect tween ratio";

    action.Update(1);
    ASSERT_EQ(action.GetTweenRatio(), 1) << "Incorrect tween ratio";

    action.Update(1);
    ASSERT_EQ(action.GetTweenRatio(), 1) << "Incorrect tween ratio";
}
