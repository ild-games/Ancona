#ifndef Ancona_Engine_Physics_VectorAction_hpp
#define Ancona_Engine_Physics_VectorAction_hpp

#include <SFML/System.hpp>

#include <Ancona/Engine/Core/Systems/Physics/Action.hpp>

namespace ild
{

/**
 * @brief A baseclass for actions that have a vector value.
 * @author Jeff Swenson
 */
class VectorAction : public Action<VectorAction>
{
    public:
        /**
         * @brief Buitder style method used to set the value of the action.
         *
         * @param value Value that the action will be set to.
         *
         * @return A reference to the action.
         */
        VectorAction * Value(sf::Vector2f value) { _value = value; return this; }

        /**
         * @brief Tween the action for the given amount of time.
         *
         * @param time Time to tween the action for.
         *
         * @return A pointer to the action.
         */
        VectorAction * Tween(float time);

        /**
         * @brief Set if the action should be taken relative to the ground.  Defaults to false.
         *
         * @param value True if the action is relative to the ground.
         *
         * @return A pointer to the action.
         */
        VectorAction * RelativeToGround(bool value) { _relativeToGround = value; return this; }

        /**
         * @copydoc ild::CameraComponent::Serialize
         */
        void Serialize(Archive & arc);

        /* getters and setters */
        float GetTweenRatio();
        const sf::Vector2f & GetValue() { return _value; }
        bool GetRelativeToGround() { return _relativeToGround; }
    private:
        /**
         * @brief Value of the action.  For a velocity action this would be the velocity.
         */
        sf::Vector2f _value;
        /**
         * @brief Amount of time the action should be tweened for.
         */
        float _tweenTime = 0;
        /**
         * @brief Flag to determine if the action should be taken relative to the ground.
         */
        bool _relativeToGround = false;
};

}
#endif
