#ifndef Test_Prototype_ImpossibleDuck_Core_PlatformBase_H_
#define Test_Prototype_ImpossibleDuck_Core_PlatformBase_H_

#include "../Input/ImpossibleInputHandler.hpp"

namespace ild
{

class PlatformBase
{
    public:
        virtual ImpossibleInputHandler * inputHandler() = 0;

};

}

#endif
