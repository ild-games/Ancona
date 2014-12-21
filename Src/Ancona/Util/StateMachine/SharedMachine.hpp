#ifndef Src_Ancona_Util_StateMachine_SharedMachine_H_
#define Src_Ancona_Util_StateMachine_SharedMachine_H_

#include <vector>


namespace ild
{

typedef int MachineState;

#define StateType(TypeName) namespace TypeName { enum Type : MachineState {
#define EndStateType ,Count }; }

/**
 * @brief Used to create a state machine that is shared by multiple objects.
 * @author Jeff Swenson
 */
template <class T, class R, class ... ArgsT>
class SharedMachine
{
    public:
        /**
         * @brief Construct and initialize a shared machine
         *
         * @param stateCount The number of states the machine should contain
         */
        SharedMachine(int maxState) : _actions(maxState, nullptr)
        {

        }

        /**
         * @brief Method Type used by the state machine
         *
         * @param MachineState State the machine is currently in. The machine action may mutate state to change the machine's state.
         * @param ArgsT... The arguments to be passed to the action.
         *
         * @return The result of the action.
         */
        typedef R (T::*MachineAction)(MachineState & state, ArgsT...);

        /**
         * @brief Set the action for the state.
         *
         * @param state State to have the action set.
         * @param action Action to be used for the state.
         */
        void SetAction(const MachineState & state, MachineAction action) 
        {
            _actions[state] = action;
        }

        /**
         * @brief Fire the action corresponding to the state on the object.
         *
         * @param object Object that the action method will be called on.
         * @param state State that the object's machine is currently in.  May be mutated by the action to change to the state.
         * @param args Arguments to be passed to the action.
         *
         * @return The result of the action.
         */
        R Update(T & object, MachineState & state, ArgsT ... args) 
        {
            return (object.*_actions[state])(state, args ...);
        }
    private:
        std::vector<MachineAction> _actions;
};

}
#endif
