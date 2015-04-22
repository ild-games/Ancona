#ifndef Test_Prototype_ImpossibleDuck_Input_ImpossibleTouch_H_
#define Test_Prototype_ImpossibleDuck_Input_ImpossibleTouch_H_

#include "ImpossibleInputHandler.hpp"

namespace ild
{


    class ImpossibleTouch : public ImpossibleInputHandler
    {
    public:
        void HandleInput() override;
    };

}

#endif