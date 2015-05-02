#ifndef Ancona_Platformer_Physics_Action_hpp
#define Ancona_Platformer_Physics_Action_hpp

#include <Ancona/Framework/Serializing/Serializing.hpp>
#include <Ancona/Util/Assert.hpp>

namespace ild
{

/**
 * @brief An action is used to interact with the physics system. (UNIT TESTED)
 * @author Jeff Swenson
 */
template <class SubClass>
class Action
{
    public:
        /**
         * Action is initialized with a priority of 0 and a duration of INSTANT.
         */
        Action() {};

        /**
         * @brief Builder method used to set the priority of the action.
         *
         * @param priority priority of the action.  Lower priority actions are applied before higher priority actions.
         *
         * @return A pointer to the action.
         */
        SubClass * priority(int priority) { _priority = priority; return static_cast<SubClass *>(this); }

        /**
         * @brief Builder method used to set the duration of the action.
         *
         * @param duration duration of the action.  An action with a duration of 0 will expire after a single update step.  The
         * duration is the number of seconds the action should apply for.
         *
         * @return A pointer to the action.
         */
        SubClass * duration(float duration) { _duration = duration; return static_cast<SubClass *>(this); }

        /**
         * @brief Reset the age of the action to zero.  This is useful if you want to retween a value.
         *
         * @return A pointer to the action.
         */
        SubClass * ResetAge() { _age = 0; return static_cast<SubClass *>(this); }

        /**
         * Stop any affects that the action has.  Once cancel is called Done will return true.
         */
        void Cancel() 
        {
            _duration = -1;         
        };

        /**
         * @brief Apply the delta to the Action.  This is used to determine when the action should no longer be in effect.
         * @return If the Update will cause the Action to be Done then it will return amount that the _age overflowed.
         */
        float Update(float delta) 
        {
            _age += delta;
            if(_age > 1 && _age - delta < 1)
            {
                return _age - 1;
            }
            return 0;
        }

        /**
         * @brief Check to see if an action has run for its entire duration. If an action is done then no other methods can be called
         * on it.
         *
         * @return True if the action is finished.  False otherwise.
         */
        bool Done() 
        {
            return _duration < _age;
        }

        void Serialize(Archive & arc)
        {
            arc(_duration, "duration");
            arc(_age, "age");
            arc(_priority, "priority");
        }

        /* getters and setters */
        int priority() { return _priority; }
        float duration() { return _duration; }
        float age() { return _age; }
    private:
        int _priority = 0;
        float _duration = 0;
        float _age = 0;
};

}
#endif
