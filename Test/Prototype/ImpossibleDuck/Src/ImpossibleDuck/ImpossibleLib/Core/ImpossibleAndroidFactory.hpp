#ifndef Test_Prototype_ImpossibleDuck_Core_ImpossibleAndroidFactory_H_
#define Test_Prototype_ImpossibleDuck_Core_ImpossibleAndroidFactory_H_

#include "ImpossiblePlatformFactory.hpp"
#include "../Input/ImpossibleTouch.hpp"

namespace ild
{

class ImpossibleAndroidFactory : public ImpossiblePlatformFactory
{
    public:
        ImpossibleTouch * inputHandler() override;
};

}

#endif
