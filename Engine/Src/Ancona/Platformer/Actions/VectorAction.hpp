#ifndef Ancona_Platformer_Action_VectorAction_hpp
#define Ancona_Platformer_Action_VectorAction_hpp

#include <SFML/System.hpp>

#include "Action.hpp"

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
         * @brief Builder style method used to set the value of the action.
         *
         * @param value value that the action will be set to.
         *
         * @return A reference to the action.
         */
        VectorAction * value(sf::Vector2f value) { _value = value; return this; }

        /**
         * @brief tween the action for the given amount of time.
         *
         * @param time Time to tween the action for.
         *
         * @return A pointer to the action.
         */
        VectorAction * tween(float time);

        /**
         * @copydoc ild::CameraComponent::Serialize
         */
        void Serialize(Archive & arc);


        /* getters and setters */
        float tweenRatio();
        const sf::Vector2f & value() { return _value; }
    private:
        /**
         * @brief value of the action.  For a velocity action this would be the velocity.
         */
        sf::Vector2f _value;
        /**
         * @brief Amount of time the action should be tweened for.
         */
        float _tweenTime = 0;
};

}
#endif
