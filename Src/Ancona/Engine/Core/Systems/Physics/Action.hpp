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
         * Action is initialized with a priority of 0 and a duration of INSTANT.
         */
        Action();

        /**
         * @brief Builder method used to set the priority of the action.
         *
         * @param priority Priority of the action.  Lower priority actions are applied before higher priority actions.
         *
         * @return A reference to the action.
         */
        Action & Priority(int priority) { _priority = priority; }

        /**
         * @brief Builder method used to set the duration of the action.
         *
         * @param duration Duration of the action.  An action with a duration of 0 will expire after a single update step.  The 
         * duration is the number of seconds the action should apply for.
         *
         * @return A reference to the action.
         */
        Action & Duration(float duration) { _duration = duration; }

        /**
         * Stop any affects that the action has.  Once cancel is called Done will return true.
         */
        void Cancel();

        /**
         * @brief Apply the delta to the Action.  This is used to determine when the action should no longer be in effect.
         */
        void Update(float delta);

        /**
         * @brief Check to see if an action has run for its entire duration. If an action is done then no other methods can be called
         * on it.
         *
         * @return True if the action is finished.  False otherwise.
         */
        inline bool Done() { return _duration >= 0; }

        inline int GetPriority() 
        { 
            return _priority;
        }

        inline float GetDuration() 
        { 
            return _duration;
        }
    private:
        int _priority;
        float _duration;
};

}
#endif
