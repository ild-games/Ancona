#ifndef Ancona_Platformer_Action_ScaleAction_hpp
#define Ancona_Platformer_Action_ScaleAction_hpp

#include <SFML/System.hpp>

#include "ValueAction.hpp"

namespace ild
{

template<typename T>
class ScaleAction : public ValueAction<T>
{
    public:
        ScaleAction(std::string drawableKey = "") : _drawableKey(drawableKey)
        {
        }

        /* getters and setters */
        std::string drawableKey() { return _drawableKey; }
        void drawableKey(std::string newDrawableKey) { _drawableKey = newDrawableKey; }
    private:
        std::string _drawableKey = "";
};

}

#endif
