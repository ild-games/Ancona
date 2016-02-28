#ifndef Ancona_Platformer_Action_RunAction_hpp
#define Ancona_Platformer_Action_RunAction_hpp

#include "VectorAction.hpp"

namespace ild
{

enum RunEvent
{
    MoveLeft,
    MoveRight,
    StopMoveLeft,
    StopMoveRight
};

class RunAction : public Action<RunAction>
{
    public:
        void AddEvent(RunEvent event);
        void ApplyRunEvents();
        void Cancel() override;

        void Serialize(Archive & arc);

        /* getters and setters */
        float maxSpeed() { return _maxSpeed; }
        float currentSpeed() { return _currentSpeed; }
        std::shared_ptr<VectorAction> velocityAction() { return _velocityAction; }
        RunAction * maxSpeed(float maxSpeed) { _maxSpeed = maxSpeed; return this; }
        RunAction * currentSpeed(float currentSpeed) { _currentSpeed = currentSpeed; return this; }
        RunAction * acceleration(float acceleration) { _acceleration = acceleration; return this; }
        RunAction * velocityAction(std::shared_ptr<VectorAction> velocityAction) { _velocityAction = velocityAction; return this; }

    private:
        float _maxSpeed = 0.0f;
        float _currentSpeed = 0.0f;
        float _acceleration = 0.0f;
        std::shared_ptr<VectorAction> _velocityAction;
        std::vector<RunEvent> _events;

        void GravitateTowards(float destination);
};

}

#endif
