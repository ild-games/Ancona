#ifndef Test_Prototype_ImpossibleDuck_Input_ImpossibleKeyboard_H_
#define Test_Prototype_ImpossibleDuck_Input_ImpossibleKeyboard_H_

#include "ImpossibleInputHandler.hpp"

namespace ild
{


class ImpossibleKeyboard : public ImpossibleInputHandler
{
    public:
        virtual void HandleInput() override;

};

}

#endif
