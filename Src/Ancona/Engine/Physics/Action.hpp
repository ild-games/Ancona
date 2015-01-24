#ifndef Ancona_Engine_Physics_Action_hpp
#define Ancona_Engine_Physics_Action_hpp

#include <Ancona/Util/Assert.hpp>

namespace ild
{

/**
 * @brief An action is used to interact with the physics system.
 * @author Jeff Swenson
 */
class Action
{
    public:
        /**
         * @brief Create an Action.  The action is initialized with a priority and duration of 0.
         */
        Action();

        /**
         * @brief Builder method used to set the priority of the action.
         *
         * @param priority Priority of the action.  Lower priority actions are applied before higher priority actions.
         *
         * @return A reference to the action.
         */
        Action & Priority(int priority);
        /**
         * @brief Builder method used to set the duration of the action.
         *
         * @param duration Duration of the action.  An action with a duration of 0 will expire after a single update step.  The 
         * duration is the number of seconds the action should apply for.
         *
         * @return A reference to the action.
         */
        Action & Duration(float duration);

        /**
         * @brief Check to see if an action has run for its entire duration. If an action is done then no other methods can be called
         * on it.
         *
         * @return True if the action is finished.  False otherwise.
         */
        inline bool Done() { return  };

        inline int GetPriority() 
        { 
            Assert(_action, "Can not call a method on a Done Action");
            return _priority->GetPriority();
        }

        inline float GetDuration() 
        { 
            Assert(_action, "Can not call a method on a Done Action");
            return _action->GetDuration();
        }

        /**
         * @brief Used to clean up the _action reference.
         */
        virtual ~Action();
    private:
        ActionDescriptor * _action;
};

}
#endif
