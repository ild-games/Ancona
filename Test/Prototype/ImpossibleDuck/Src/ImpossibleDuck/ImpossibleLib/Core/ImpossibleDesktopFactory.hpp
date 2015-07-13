#ifndef Test_Prototype_ImpossibleDuck_Core_ImpossibleDesktopFactory_H_
#define Test_Prototype_ImpossibleDuck_Core_ImpossibleDesktopFactory_H_

#include "ImpossiblePlatformFactory.hpp"
#include "../Input/ImpossibleKeyboard.hpp"

namespace ild
{

class ImpossibleDesktopFactory : public ImpossiblePlatformFactory
{
    public:
        ImpossibleKeyboard * inputHandler() override;
};

}

#endif
