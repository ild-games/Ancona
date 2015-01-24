#ifndef Ancona_Engine_Physics_ActionDescriptor_hpp
#define Ancona_Engine_Physics_ActionDescriptor_hpp

/**
 * @brief State for an action that is stored within the Physics System.
 * @author Jeff Swenson
 */
class ActionDescriptor
{
    public:

        /**
         * @brief Used to clean up the _proxy reference.
         */
        virtual ~ActionDescriptor();

        inline int GetPriority() { return _priority; }
        inline float GetDuration() { return _duration; }
    private:
        Action * _proxy;
        float _duration; 
        int  _priority;
};

#endif
