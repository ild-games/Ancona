#ifndef Test_Prototype_ImpossibleDuck_Core_ImpossiblePlatformFactory_H_
#define Test_Prototype_ImpossibleDuck_Core_ImpossiblePlatformFactory_H_

#include "../Input/ImpossibleInputHandler.hpp"

namespace ild
{

class ImpossiblePlatformFactory
{
    public:
        virtual ImpossibleInputHandler * inputHandler() = 0;

};

}

#endif
