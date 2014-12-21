#include <gtest/gtest.h>

#include <Ancona/Util/StateMachine/SharedMachine.hpp>

using namespace ild;

StateType(TestState)
    State1,
    State2,
    State3
EndStateType

/*
enum TestState : int 
{
   State1,
   State2,
   State3,
   StateCount
};
*/


StateType(BoolState)
    True,
    False
EndStateType

class SharedMachineUser {
    public:
        MachineState state;

        SharedMachineUser()
        {
            state = TestState::State1;
        }

        bool Method1(MachineState & current, MachineState next) 
        {
            bool correct = current == TestState::State1;
            current = next;
            return correct;
        }

        bool Method2(MachineState & current, MachineState next) 
        {
            bool correct = current == TestState::State2;
            current = next;
            return correct;
        }

        bool Method3(MachineState & current, MachineState next) 
        {
            bool correct = current == TestState::State3;
            current = next;
            return correct;
        }
};

class NoArgumentUser 
{
    public:
        MachineState state;

        NoArgumentUser(BoolState::Type init)
        {
            state = init;
        }

        bool TrueState(MachineState & state)
        {
            return true;
        }

        bool FalseState(MachineState & state)
        {
            return false;
        }
};


TEST(SharedMachine,OneArgument) {
    SharedMachine<SharedMachineUser,bool,MachineState> machine(TestState::Count);
    machine.SetAction(TestState::State1, &SharedMachineUser::Method1);
    machine.SetAction(TestState::State2, &SharedMachineUser::Method2);
    machine.SetAction(TestState::State3, &SharedMachineUser::Method3);

    SharedMachineUser user;
    user.state = TestState::State1;

    ASSERT_TRUE(machine.Update(user, user.state, TestState::State2)) << "First State Call Failed"; 
    ASSERT_TRUE(machine.Update(user, user.state, TestState::State3)) << "Second State Call Failed"; 
    ASSERT_TRUE(machine.Update(user, user.state, TestState::State1)) << "Third State Call Failed"; 
}

TEST(SharedMachine,NoArgument) {
    SharedMachine<NoArgumentUser, bool> machine(BoolState::Count);
    NoArgumentUser user(BoolState::False);

    machine.SetAction(BoolState::True,&NoArgumentUser::TrueState);
    machine.SetAction(BoolState::False,&NoArgumentUser::FalseState);
    
    ASSERT_FALSE(machine.Update(user, user.state)) << "True State Method Called When False Method Expected"; 
    user.state = BoolState::True;
    ASSERT_TRUE(machine.Update(user, user.state)) << "False State Method Called When True Method Expected"; 
}
