#ifndef Ancona_Engine_Physics_VectorAction_hpp
#define Ancona_Engine_Physics_VectorAction_hpp

#include <Ancona/Engine/Core/Systems/Physics/Action.hpp>

namespace ild
{

/**
 * @brief A baseclass for actions that have a vector value.
 * @
 */
class VectorAction : public Action
{
    public:
        /**
         * @brief Buitder style method used to set the value of the action.
         *
         * @param value Value that the action will be set to.
         *
         * @return A reference to the action.
         */
        Action & Value(sf::Vector2f value) { _value = value; }

        const sf::Vector2f & GetValue() { return _value; }
         
    private:
        sf::Vector2f _value;
};

}
#endif
