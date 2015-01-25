#ifndef Ancona_Engine_Physics_VectorAction_hpp
#define Ancona_Engine_Physics_VectorAction_hpp

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
        Action & Value(const sf::Vector2f value);
         
    private:
        sf::Vector2f _value;


}
#endif
