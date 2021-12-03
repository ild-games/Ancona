#ifndef Ancona_Platformer_Action_ValueAction_hpp
#define Ancona_Platformer_Action_ValueAction_hpp

#include "Action.hpp"

namespace ild
{

/**
 * @brief A baseclass for actions that have a vector value.
 * @author Jeff Swenson
 */
template <typename T> class ValueAction : public Action<ValueAction<T>>
{
  public:
    /**
     * @brief Builder style method used to set the value of the action.
     *
     * @param value value that the action will be set to.
     *
     * @return A reference to the action.
     */
    ValueAction<T> *value(T value)
    {
        _value = value;
        return this;
    }

    /**
     * @brief tween the action for the given amount of time.
     *
     * @param time Time to tween the action for.
     *
     * @return A pointer to the action.
     */
    ValueAction<T> *tween(float time)
    {
        _tweenTime = time;
        return this;
    }

    /**
     * @copydoc ild::CameraComponent::Serialize
     */
    void Serialize(Archive &arc)
    {
        Action<ValueAction<T>>::Serialize(arc);
        arc(_tweenTime, "tween");
        arc(_value, "value");
    }

    /* getters and setters */
    float tweenRatio()
    {
        if (_tweenTime > 0)
        {
            return std::min(Action<ValueAction<T>>::age() / _tweenTime, 1.0f);
        }
        else
        {
            return 1;
        }
    }
    const T &value()
    {
        return _value;
    }

  private:
    /**
     * @brief value of the action.  For a velocity action this would be the velocity.
     */
    T _value;
    /**
     * @brief Amount of time the action should be tweened for.
     */
    float _tweenTime = 0;
};

} // namespace ild
#endif
