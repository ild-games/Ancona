#ifndef Ancona_Platformer_Action_JumpAction_hpp
#define Ancona_Platformer_Action_JumpAction_hpp

#include "VectorAction.hpp"

namespace ild
{

enum JumpEvent
{
    Stop,
    HitCeiling,
    LetGo
};

class JumpAction : public Action<JumpAction>
{
    public:
        void AddEvent(JumpEvent event);
        void ApplyJumpEvents(sf::Vector2f totalGravity);
        void Cancel() override;

        /**
         * @copydoc ild::CameraComponent::Serialize
         */
        void Serialize(Archive & arc);

        /* getters and setters */
        float jumpSpeed() { return _jumpSpeed; }
        JumpAction * jumpSpeed(float jumpSpeed);
        JumpAction * velocityAction(std::shared_ptr<VectorAction> velocityAction) { _velocityAction = velocityAction; return this; }
        JumpAction * reducedByPercentage(float reducedByPercentage) { _reducedByPercentage = reducedByPercentage; return this; }

    private:
        float _jumpSpeed = 0.0f;
        float _reducedByPercentage = 0.0f;
        std::shared_ptr<VectorAction> _velocityAction;
        std::vector<JumpEvent> _events;

        sf::Vector2f JumpGravityDifference(sf::Vector2f totalGravity);

};

}


#endif
